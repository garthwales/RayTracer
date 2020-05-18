#include "Octahedron.h"

#include "utility.h"


Octahedron::Octahedron() : Object() {
}

Octahedron::Octahedron(const Octahedron& octahedron) : Object(octahedron) {

}

Octahedron::~Octahedron() {

}

Octahedron& Octahedron::operator=(const Octahedron& octahedron) {
	if (this != &octahedron) {
		Octahedron::operator=(octahedron);
	}
	return *this;
}

std::vector<RayIntersection> Octahedron::intersect(const Ray& ray) const {
	std::vector<RayIntersection> result;

	/**
	 * The intersection of a Ray with an Octahedron can be approached in a few ways. 
	 * The basic constraint for a point on the surface of the base Octahedron is \(|x| + |y| + |z| = 1\). 
	 * 
	 * A simple, but not very elegant, way to approach this is to consider the eight faces independently, 
	 * and intersect the ray with each of them in turn. For example, 
	 * the face with negative \(Z\)- and positive \(X\)- and \(Y\)-values is defined by \( x + y - z = 1\).
	 */
    Ray inverseRay = transform.applyInverse(ray);

    double z0 = inverseRay.point(2);
    double dz = inverseRay.direction(2);
    double y0 = inverseRay.point(1);
    double dy = inverseRay.direction(1);
    double x0 = inverseRay.point(0);
    double dx = inverseRay.direction(0);

	// point + t*direction = (x0,y0,z0) + t(dx,dy,dz)
	//

	// x = 1, y = 1, z = 1
	std::array<Point, 3> face1 = {Point(1,0,0), Point(0,-1,0), Point(0,0,1)}; // top tri with +x, +z
	std::array<Point, 3> face2 = {Point(1,0,0), Point(0,1,0), Point(0,0,1)}; // bottom tri with +x, +z
	std::array<Point, 3> face3 = {Point(-1,0,0), Point(0,-1,0), Point(0,0,1)}; // top tri with -x, +z
	std::array<Point, 3> face4 = {Point(-1,0,0), Point(0,1,0), Point(0,0,1)}; // bottom tri with -x, +z
	std::array<Point, 3> face5 = {Point(-1,0,0), Point(0,-1,0), Point(0,0,-1)}; // top tri with -x, -z
	std::array<Point, 3> face6 = {Point(-1,0,0), Point(0,1,0), Point(0,0,-1)}; // bottom tri with -x, -z
	std::array<Point, 3> face7 = {Point(1,0,0), Point(0,-1,0), Point(0,0,-1)}; // top tri with +x, -z
	std::array<Point, 3> face8 = {Point(1,0,0), Point(0,1,0), Point(0,0,-1)}; // bottom tri with +x, -z

	// Array containing the points of each faces triangle.
	std::array<std::array<Point, 3>,8> faces = {face1, face2, face3, face4, face5, face6, face7, face8};

	for (const auto & face : faces) {
		// It'd be quicker to project the triangle onto an axis
		// aligned plane and then do calculations in 2D.

		// Because of form of the octahedron we have a
		// triangle have vertices along each axis so
		// have the following vertices:

		Point A = face[0]; // x vertex of triangle
		Point B = face[1]; // y vertex of triangle
		Point C = face[2]; // z vertex of triangle

		// Normal of the plane of intersection
		// (the normal of this portion of octahedron)
		Normal n = (B-A).cross(C-A);
		n /= n.norm();

		// The plane of intersection 
		// (The normal dotted with any point in plane)
		double d = n.dot(A);

		// solve for t in equation, ray = point + t*direction.
		double t = (d - n.dot(inverseRay.point)) / n.dot(inverseRay.direction);
		
		// If the intersection is in front of ray.
		if(t > 0) {
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			// Check if within the triangle region
			// For each edge, AB, AC, CB
			// the cross product of edge and point with vertex
			// should point in the same direction as the normal
			// so
			// ((B-A)x(hit-A).n >= 0)
			// ((C-B)x(hit-B).n >= 0)
			// ((A-C)x(hit-C).n >= 0)
			// and if all three are true then point within triangle
			// (= to include the edges)
			if ((B-A).cross(hit.point-A).dot(n) >= 0
					&& (C-B).cross(hit.point-B).dot(n) >= 0
					&& (A-C).cross(hit.point-C).dot(n) >= 0) {
				// then do the usual hit
				hit.point = transform.apply(hit.point);
				hit.material = material;
				hit.normal = transform.apply(n);
				if(hit.normal.dot(ray.direction) > 0) {
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
	}

	return result;
}
