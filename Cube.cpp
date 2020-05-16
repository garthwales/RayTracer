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

    double tz0 = (-1 - z0)/dz;
    double tz1 = (1 - z0)/dz;
    double ty0 = (-1 - y0)/dy;
    double ty1 = (1 - y0)/dy;
    double tx0 = (-1 - x0)/dx;
    double tx1 = (1 - x0)/dx;

    RayIntersection hit;

    //0 division check
    if((std::abs(dx) < epsilon) || (std::abs(dy) < epsilon) || (std::abs(dz) < epsilon)){
        return result;
    }

    /**check both intersections are > 0 and compute details of hit point, then change the
       hitpoint and compute for that hitpoint. Repeat these steps for the next two pairs
       of hitpoints **/
    if( tz0 > 0 && tz1 > 0){
        hit.point = inverseRay.point + tz0 * inverseRay.direction;
        if((hit.point(0) > -1 && hit.point(0) < 1) && (hit.point(1) > - 1 && hit.point(1) < 1)){
            hit.material = material;
            hit.point = transform.apply(Point(hit.point));
            hit.normal = transform.apply(Normal(0, 0, -1));
            if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
            hit.distance =  (hit.point - ray.point).norm();
            result.push_back(hit);
        }
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


