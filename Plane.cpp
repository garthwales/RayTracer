#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	Ray inverseRay = transform.applyInverse(ray);

	double  z0 = inverseRay.point (2);
	double  dz = inverseRay.direction (2);

	if (std::abs(dz) > epsilon) {
		double t = -z0/dz;
		if (t > epsilon) {
			// Hit is in front of ray
			RayIntersection  hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			if(std::abs(hit.point(0)) < 1 && std::abs(hit.point(1)) < 1) {
				// In square region -- compute hit point details
				hit.point = transform.apply(hit.point);
				hit.material = material;
				hit.normal = transform.apply(Normal(0,0,1));
				if (hit.normal.dot(ray.direction) > 0) {
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
	}
	

	return result;
}