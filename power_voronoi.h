#ifndef VORONOI_H
#define VORONOI_H

#include <vector>
#include "vector.h"
#include "writer.h"

Polygon power_clip_polygon(const Polygon& subjectPolygon, const Polygon& clipPolygon);
Polygon power_create_halfplane(const Vector& Pi, const Vector& Pj, double wi, double wj);
std::vector<Polygon> power_voronoi(const std::vector<Vector>& sites, const std::vector<double>& weights, const Polygon& bounding_box);

#endif
