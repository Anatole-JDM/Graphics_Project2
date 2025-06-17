#ifndef VORONOI_H
#define VORONOI_H

#include <vector>
#include "vector.h"
#include "writer.h"

Polygon clip_polygon(const Polygon& subjectPolygon, const Polygon& clipPolygon);
Polygon create_halfplane(const Vector& Pi, const Vector& Pj);
std::vector<Polygon> voronoi(const std::vector<Vector>& sites, const Polygon& bounding_box);

#endif
