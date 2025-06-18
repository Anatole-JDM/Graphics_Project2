#include "voronoi.h"
#include <iostream>

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