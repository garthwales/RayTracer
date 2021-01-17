# RayTracer
The C++ implementation of a few methods in a ray tracer framework.

The files present are the files created by myself which are the best examples of the work done here, most of the rest were a part of the existing framework.

My proudest piece is Octahedron.cpp. The octahedron has 8 triangles that we check intersections against. 
For each edge of the triangle (A,B,C) we check the cross product of the edge and point with the vertex, it should point in the same direction as the normal (i.e. (B-A)x(hit-A).n >= 0). 

If this applies to each vertex then the intersection is within this triangle.


See [RaytracerReport.pdf](https://github.com/GenericPath/RayTracer/blob/master/Raytracer%20Report.pdf) for the full explanation of what else is implemented here.
