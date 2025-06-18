#include "power_voronoi.h"
#include "writer.h"
#include <vector>
#include <iostream>

int main() {
    // Same sites as in test_voronoi.cpp
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

    // Define weights for each site (varying weights to demonstrate the effect)
    std::vector<double> weights = {
        0.02,   // Small weight for site 0
        0.05,   // Medium weight for site 1
        0.01,   // Very small weight for site 2
        0.03,   // Small-medium weight for site 3
        0.01,   // Very small weight for site 4
        0.1,    // Largest weight for site 5 (center)
        0.02,   // Small weight for site 6
        0.06,   // Medium-large weight for site 7
        0.04    // Medium weight for site 8
    };

    // Create bounding box
    Polygon bounding_box;
    bounding_box.vertices = {
        Vector(0.0, 0.0, 0.0),
        Vector(1.0, 0.0, 0.0),
        Vector(1.0, 1.0, 0.0),
        Vector(0.0, 1.0, 0.0)
    };

    // Compute power Voronoi diagram
    std::vector<Polygon> cells = power_voronoi(sites, weights, bounding_box);
    
    // Save the diagram to an SVG file
    save_svg(cells, "test_power_voronoi.svg", "none");
    
    // Also save with site indices visible (to compare weights with cell sizes)
    for (size_t i = 0; i < sites.size(); i++) {
        std::cout << "Site " << i << " at (" << sites[i][0] << ", " << sites[i][1] 
                  << ") has weight " << weights[i] << std::endl;
    }
    
    std::cout << "Power Voronoi diagram created and saved to test_power_voronoi.svg" << std::endl;
    
    return 0;
}