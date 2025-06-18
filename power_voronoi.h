#ifndef VORONOI_H
#define VORONOI_H

#include <vector>
#include "vector.h"
#include "writer.h"

Polygon power_clip_polygon(const Polygon& subjectPolygon, const Polygon& clipPolygon);
Polygon power_create_halfplane(const Vector& Pi, const Vector& Pj, double wi, double wj);
std::vector<Polygon> power_voronoi(const std::vector<Vector>& sites, const std::vector<double>& weights, const Polygon& bounding_box);

struct SDOTContext {
    std::vector<Vector> sites;
    std::vector<double> lambdas;
    Polygon bounding_box;
};

double cell_area(const Polygon& poly);
double norm_integral(const Polygon& poly, const Vector& site);

#include "lbfgs.h"

lbfgsfloatval_t evaluate(
    void *instance,
    const lbfgsfloatval_t *w, // current weights
    lbfgsfloatval_t *g,       // gradient (to be filled)
    const int n,
    const lbfgsfloatval_t step
);

#endif
