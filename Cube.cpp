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
    //transforming ray
    Ray inverseRay = transform.applyInverse(ray);

    //more intersection points now
    double z0 = inverseRay.point(2);
    double dz = inverseRay.direction(2);
    double y0 = inverseRay.point(1);
    double dy = inverseRay.direction(1);
    double x0 = inverseRay.point(0);
    double dx = inverseRay.direction(0);
    
    // check for division by 0
    if((std::abs(dx) < epsilon) || (std::abs(dy) < epsilon) || (std::abs(dz) < epsilon)){
        return result;
    }

    // Ray = point + t*direction
    // so find t on each axis (x,y,z)
    // that equals 1 or -1
    // If t > 0 then the intersection
    // is in front of camera, so is a hit.

    // (this gives us the plane of intersection)

    double tz0 = (-1 - z0)/dz; // intersection with +1 z plane
    double tz1 = (1 - z0)/dz; // intersection with -1 z plane
    double ty0 = (-1 - y0)/dy; // intersection with +1 y plane
    double ty1 = (1 - y0)/dy; // intersection with -1 y plane
    double tx0 = (-1 - x0)/dx; // intersection with +1 x plane
    double tx1 = (1 - x0)/dx; // intersection with -1 x plane

    RayIntersection hit;

    // Check both intersections are > 0 and compute details of hit point, then change the
    // hitpoint and compute for that hitpoint. 
    // Repeat these steps for the next two pairs of hitpoints.
    if( tz0 > 0 && tz1 > 0){
        hit.point = inverseRay.point + tz0 * inverseRay.direction;
        // point is within a visible plane of intersection with the cube
        if((hit.point(0) > -1 && hit.point(0) < 1) && (hit.point(1) > - 1 && hit.point(1) < 1)){
            // point is within the unit square, so this face of the cube
            hit.material = material;
            hit.point = transform.apply(Point(hit.point));
            hit.normal = transform.apply(Normal(0, 0, -1));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
        // same thing but for the other plane of intersection
        hit.point = inverseRay.point + tz1 * inverseRay.direction;
        if((hit.point(0) > -1 && hit.point(0) < 1) && (hit.point(1) > - 1 && hit.point(1) < 1)){
            hit.material = material; 
            hit.point = transform.apply(Point(hit.point));
            hit.normal = transform.apply(Normal(0, 0, 1));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
    }
    // same as above, but for y planes instead of z planes
    if(ty0 > 0 && ty1 > 0){
        hit.point = inverseRay.point + ty0 * inverseRay.direction;
        if((hit.point(0) > -1 && hit.point(0) < 1) && (hit.point(2) > - 1 && hit.point(2) < 1)){
            hit.material = material;
            hit.point = transform.apply(Point(hit.point));                
            hit.normal = transform.apply(Normal(0, -1, 0));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
        hit.point = inverseRay.point + ty1 * inverseRay.direction;
        if((hit.point(0) > -1 && hit.point(0) < 1) && (hit.point(2) > - 1 && hit.point(2) < 1)){
            hit.material = material;               
            hit.point = transform.apply(Point(hit.point));               
            hit.normal = transform.apply(Normal(0, 1, 0));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
    }
    // // same as above, but for x planes instead of z/y planes
    if(tx0 > 0 && tx1 > 0){
        hit.point = inverseRay.point + tx0 * inverseRay.direction;
        if((hit.point(1) > -1 && hit.point(1) < 1) && (hit.point(2) > - 1 && hit.point(2) < 1)){
            hit.material = material;               
            hit.point = transform.apply(Point(hit.point));               
            hit.normal = transform.apply(Normal(-1, 0, 0));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
        hit.point = inverseRay.point + tx1 * inverseRay.direction;
        if((hit.point(1) > -1 && hit.point(1) < 1) && (hit.point(2) > - 1 && hit.point(2) < 1)){
            hit.material = material;               
            hit.point = transform.apply(Point(hit.point));              
            hit.normal = transform.apply(Normal(1, 0, 0));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
    }

    return result;
}


