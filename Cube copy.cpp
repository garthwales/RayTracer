/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;
	
	Ray inverseRay = transform.applyInverse(ray);

	double  x0 = inverseRay.point (0);
	double  dx = inverseRay.direction (0);

	double  y0 = inverseRay.point (1);
	double  dy = inverseRay.direction (1);

	double  z0 = inverseRay.point (2);
	double  dz = inverseRay.direction (2);

	// catch division by 0
	if(std::abs(dx) < epsilon || std::abs(dy) < epsilon || std::abs(dz) < epsilon) {
		return result;
	}

	double tx0 = (-1 - x0)/dx;
    double tx1 = (1 - x0)/dx;
    double ty0 = (-1 - y0)/dy;
    double ty1 = (1 - y0)/dy;
	double tz0 = (-1 - z0)/dz;
    double tz1 = (1 - z0)/dz;
    

	RayIntersection  hit;

	if (tz0 > 0 && tz1 > 0) {
		hit.point = inverseRay.point + tz * inverseRay.direction;
		if (std::abs(hit.point(0)) < 1 && std::abs(hit.point(1)) < 1) {
			// In square region -- compute hit point details
			hit.point = transform.apply(hit.point);
			hit.material = material;
			hit.normal = transform.apply(Normal(0, 0, 1));
			// if (hit.normal.dot(ray.direction) > 0) {
			// 	hit.normal = -hit.normal;
			// }
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	if (ty0 > 0 && ty1 > 0) {
		hit.point = inverseRay.point + ty * inverseRay.direction;
		if (std::abs(hit.point(0)) < 1 && std::abs(hit.point(2)) < 1) {
			// In square region -- compute hit point details
			hit.point = transform.apply(hit.point);
			hit.material = material;
			hit.normal = transform.apply(Normal(0, 1, 0));
			// if (hit.normal.dot(ray.direction) > 0) {
			// 	hit.normal = -hit.normal;
			// }
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	if (tx0 > 0 && tx1 > 0) {
		hit.point = inverseRay.point + tx * inverseRay.direction;
		if (std::abs(hit.point(1)) < 1 && std::abs(hit.point(2)) < 1) {
			// In square region -- compute hit point details
			hit.point = transform.apply(hit.point);
			hit.material = material;
			hit.normal = transform.apply(Normal(1, 0, 0));
			// if (hit.normal.dot(ray.direction) > 0) {
			// 	hit.normal = -hit.normal;
			// }
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}
	
	// for(int i=0; i <= 2; i++) {
	// 	double coord = inverseRay.point(i);
	// 	double d = inverseRay.direction(i);

	// 	if(d < epsilon) return result;

	// 	if(std::abs(d) < epsilon) break;

	// 	double t = -coord/d;
	// 	hit.point = inverseRay.point + t*inverseRay.direction;
	// 	if(std::abs(hit.point(i)) < 1) {
	// 		hit.point = transform.apply(hit.point);
	// 		hit.material = material;
	// 		switch(i) {
	// 			case 0: hit.normal = transform.apply(Normal(1,0,0));
	// 			case 1:	hit.normal = transform.apply(Normal(0,1,0));
	// 			case 2: hit.normal = transform.apply(Normal(0,0,1));
	// 		}
	// 		if (hit.normal.dot(ray.direction) > 0) {
	// 				hit.normal = -hit.normal;
	// 			}
	// 			hit.distance = (hit.point - ray.point).norm();
	// 			result.push_back(hit);
	// 	}
	// }
	return result;
}


