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
		// A = V1-V0
		// B = V2 - V0

		// R0.X + t * Rd.X = V0.X + u * A.X + v * B.X
		// R0.Y + t * Rd.Y = V0.Y + u * A.Y + v * B.Y
		// R0.Z + t * Rd.Z = V0.Z + u * A.Z + v * B.Z]
		

		// plane = ax + by + cz = d
		// so n . x = d (n = [a;b;c], x = [x;y;z])

		// triangle with A,B,C points
		// only need normal of plane
		// n = ((B-A) cross (C-A)) /= n.norm()

		// R(t) = P + td
		// t = (d - n.P) / n.d
		// (if n.d == 0 then parallel, doesn't intersect)

		// plane d = n.A (any vertice of triangle creates the plane formula)



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

		// solve for t in equation
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
		



		// Vector A = face[1] - face[0]; // Edge vector
		// Vector B = face[2] - face[0]; // Edge vector
		// Vector AB = A.cross(B);
		// AB /= AB.norm();

		// Vector p = inverseRay.direction.cross(B);
		// double a = A.dot(p);
		// if(a < epsilon) {
		// 	return result;
		// }

		// double f = 1/a;
		// Vector s = inverseRay.point - B;
		// double u = f * s.dot(p);
		// if (u < 0.0 || u > 1.0) {
		// 	return result;
		// }
		
		// Vector q = s.cross(A);
		// double v = f * inverseRay.direction.dot(q);
		// if (v < 0.0 || u+v > 0.0) {
		// 	return result;
		// }

		// double t = f * B.dot(q);
		// RayIntersection hit;
		// hit.normal = AB;
		// hit.point = inverseRay.point + t*inverseRay.direction;
		// hit.point = transform.apply(hit.point);
		// hit.material = material;
		// if (hit.normal.dot(ray.direction) > 0) {
		// 	hit.normal = -hit.normal;
		// }
		// hit.distance = (hit.point * t).norm();
		// std::cout << "Works?" << std::endl;
		// result.push_back(hit);
	}

	// https://stackoverflow.com/questions/40560000/ray-tracing-triangles
	// https://stackoverflow.com/questions/13655457/raytracing-ray-triangle-intersection
	// https://courses.cs.washington.edu/courses/csep557/10au/lectures/triangle_intersection.pdf


	return result;
}
