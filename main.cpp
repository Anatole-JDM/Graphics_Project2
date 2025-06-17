#include "voronoi.h"
#include "writer.h"
#include <vector>

int main() {
    std::vector<Vector> sites = {
        Vector(0.25, 0.25, 0.0),
        Vector(0.75, 0.25, 0.0),
        Vector(0.5,  0.75, 0.0),
        Vector(0.25, 0.75, 0.0),
        Vector(0.75, 0.75, 0.0),
        Vector(0.5,  0.5,  0.0),
        Vector(0.25, 0.5,  0.0),
        Vector(0.75, 0.5,  0.0),
        Vector(0.1,  0.1, 0.0),
    };

    Polygon bounding_box;
    bounding_box.vertices = {
        Vector(0.0, 0.0, 0.0),
        Vector(1.0, 0.0, 0.0),
        Vector(1.0, 1.0, 0.0),
        Vector(0.0, 1.0, 0.0)
    };

    std::vector<Polygon> cells = voronoi(sites, bounding_box);
    save_svg(cells, "test_voronoi.svg", "red");

    return 0;
}
