#ifndef WRITER_H
#define WRITER_H

#include <vector>
#include <string>
#include "vector.h"  // Make sure Vector is known here

class Polygon {
public:
    std::vector<Vector> vertices;
};

void save_svg(const std::vector<Polygon>& polygons, std::string filename, std::string fillcol = "none");
void save_svg_animated(const std::vector<Polygon>& polygons, std::string filename, int frameid, int nbframes);

#endif