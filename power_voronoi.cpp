#include "power_voronoi.h"
#include <iostream>
#include <cassert>
#include <algorithm>

Polygon power_clip_polygon(const Polygon& subjectPolygon, const Polygon& clipPolygon) { // implemented using the steps detailed in the course pdf for the Sutherland-Hodgman algorithm
    Polygon input = subjectPolygon;

    for (size_t e = 0; e < clipPolygon.vertices.size(); e++) {
        Polygon outPolygon;

        Vector u = clipPolygon.vertices[(e > 0) ? e - 1 : clipPolygon.vertices.size() - 1];
        Vector v = clipPolygon.vertices[e];
        Vector edge = v - u;
        Vector N(-edge[1], edge[0], 0.0);
        N.normalize();

        for (size_t i = 0; i < input.vertices.size(); i++) {
            Vector curVertex = input.vertices[i];
            Vector prevVertex = input.vertices[(i > 0) ? i - 1 : input.vertices.size() - 1];

            double curtest = dot(curVertex - u, N);
            double prevtest = dot(prevVertex - u, N);

            if (curtest >= 0) {
                if (prevtest < 0) {
                    Vector d = curVertex - prevVertex;
                    double t = dot(u - prevVertex, N) / dot(d, N);
                    Vector inter = prevVertex + d * t;
                    outPolygon.vertices.push_back(inter);
                }
                outPolygon.vertices.push_back(curVertex);
            } else if (prevtest >= 0) {
                Vector d = curVertex - prevVertex;
                double t = dot(u - prevVertex, N) / dot(d, N);
                Vector inter = prevVertex + d * t;
                outPolygon.vertices.push_back(inter);
            }
        }

        input = outPolygon;
    }

    return input;
}

Polygon power_create_halfplane(const Vector& Pi, const Vector& Pj, double wi, double wj) {
    Vector D = Pj - Pi;
    Vector M = 0.5 * (Pi + Pj);
    Vector M2 = M + (wi-wj) / (2.0 * dot(Pi - Pj, Pi - Pj)) * (Pj - Pi);
    D.normalize();
    Vector T(-D[1], D[0], 0.0);

    double len = 1000.0;

    Vector p1 = M2 + len * T;
    Vector p2 = p1 - len * D;
    Vector p3 = M2 - len * T - len * D;
    Vector p4 = M2 - len * T;

    Polygon poly;
    poly.vertices = {p1, p2, p3, p4};
    return poly;
}

std::vector<Polygon> power_voronoi(const std::vector<Vector>& sites, const std::vector<double>& weights, const Polygon& bounding_box) {
    std::vector<Polygon> cells;

    for (size_t i = 0; i < sites.size(); ++i) {
        Vector Pi = sites[i];
        double wi = weights[i];
        Polygon cell = bounding_box;

        for (size_t j = 0; j < sites.size(); ++j) {
            if (i != j) {
                Polygon halfplane = power_create_halfplane(Pi, sites[j], wi, weights[j]);
                cell = power_clip_polygon(cell, halfplane);
            }
        }
        cells.push_back(cell);
    }
    return cells;
}

double cell_area(const Polygon& poly) {
    double A = 0.0;
    for (size_t i = 0; i < poly.vertices.size(); ++i) {
        const Vector& x = poly.vertices[i];
        const Vector& y = poly.vertices[(i + 1) % poly.vertices.size()];
        A += x[0] * y[1] - y[0] * x[1];
    }
    return 0.5 * std::abs(A);
}

double norm_integral(const Polygon& poly, const Vector& site) {
    const std::vector<Vector>& v = poly.vertices;
    double integral = 0.0;

    for (size_t i = 0; i < v.size(); ++i) {
        const Vector& a = v[i];
        const Vector& b = v[(i + 1) % v.size()];

        double x0 = a[0];
        double y0 = a[1];
        double x1 = b[0];
        double y1 = b[1];

        double temp1= x0*x0 + x0*x1 + x1*x1 + y0*y0 + y0*y1 + y1*y1;
        double temp2 = -4.0 * (site[0]*(x0 + x1) + site[1]*(y0 + y1)) + 6.0 * dot(site, site);

        integral += (x0 * y1 - x1 * y0) * (temp1 + temp2);
    }

    return integral / 12.0;
}

void make_counter_clockwise(Polygon& poly) {
    double signed_area = 0.0;
    for (size_t i = 0; i < poly.vertices.size(); ++i) {
        const Vector& a = poly.vertices[i];
        const Vector& b = poly.vertices[(i+1) % poly.vertices.size()];
        signed_area += a[0]*b[1] - b[0]*a[1];
    }
    signed_area *= 0.5;
    if (signed_area < 0) {
        std::reverse(poly.vertices.begin(), poly.vertices.end());
    }
}


lbfgsfloatval_t evaluate(
    void *instance,
    const lbfgsfloatval_t *w,
    lbfgsfloatval_t *g,
    const int n,
    const lbfgsfloatval_t step
) {
    SDOTContext *ctx = (SDOTContext*)instance;
    std::vector<double> weights(w, w + n);
    std::vector<Polygon> cells = power_voronoi(ctx->sites, weights, ctx->bounding_box);

    double g_val = 0.0;

    for (int i = 0; i < n; ++i) {
        make_counter_clockwise(cells[i]);

        double area = cell_area(cells[i]);
        double integral = norm_integral(cells[i], ctx->sites[i]);

        if (g) {
            g[i] = area - ctx->lambdas[i];
        }

        g_val += integral + weights[i] * ctx->lambdas[i] - weights[i]*area;
    }

    return -g_val; 
}





