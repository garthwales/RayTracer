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

	/***************************************************
	 * Code for Ray-Octahedron intersection goes here. *
	 ***************************************************/

	return result;
}
