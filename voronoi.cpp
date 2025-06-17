#include <vector>
#include "vector.h"
#include "writer.cpp"

Polygon clip_polygon(const Polygon& subjectPolygon, const Polygon& clipPolygon) { // implemented using the steps detailed in the course pdf for the Sutherland-Hodgman algorithm
    
    Polygon input = subjectPolygon;

    for (int e = 0; e < clipPolygon.vertices.size(); e++) {
        Polygon outPolygon;
        Vector u = clipPolygon.vertices[(e > 0) ? e - 1 : input.vertices.size() - 1];
        Vector v = clipPolygon.vertices[e];
        Vector N(v[1] - u[1], u[0] - v[0], 0.0);

        for (int i = 0; i < input.vertices.size(); i++) {
            Vector curVertex = input.vertices[i];
            Vector prevVertex = input.vertices[(i > 0) ? i - 1 : input.vertices.size() - 1];

            double curtest = dot(u - curVertex, N);
            double prevtest = dot(u - prevVertex, N);

            if (curtest >= 0) {
                if (prevtest < 0) {
                    double t = dot(u - prevVertex, N) / dot(curVertex - prevVertex, N);
                    Vector intersection = prevVertex + (curVertex - prevVertex) * t;
                    outPolygon.vertices.push_back(intersection);
                }
                outPolygon.vertices.push_back(curVertex);
            } else if (prevtest >= 0) {
                double t = dot(u - prevVertex, N) / dot(curVertex - prevVertex, N);
                Vector intersection = prevVertex + (curVertex - prevVertex) * t;
                outPolygon.vertices.push_back(intersection);
            }
        }
        
        input = outPolygon; 
    }

    return input;
}
