#include "SpotLightSource.h"

#include "utility.h"

SpotLightSource::SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle) :
	LightSource(colour), location_(location), direction_(direction), angle_(angle) {

}

SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  location_(lightSource.location_), direction_(lightSource.direction_), angle_(lightSource.angle_) {

}

SpotLightSource::~SpotLightSource() {

}

SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		location_ = lightSource.location_;
		direction_ = lightSource.direction_;
		angle_ = lightSource.angle_;
	}
	return *this;
}

Colour SpotLightSource::getIlluminationAt(const Point& point) const {
	/**
	 * Caculate vector from cone to point, and normalise.
	 * Normalise the lights direction vector.
	 * Take the dot product of these two normalised directions.
	 * The dot product between two normal vectors is the cosine of angle between them.
	 * Thus, take arccos (acos in c++) of their dot product to get the angle.
	 * If angle is < angle_ then point is within the spotlight.
	 */

	// Unit direction from cone to point
	Direction lightNorm = (point - location_);
	lightNorm /= lightNorm.norm();

	// Unit direction from light
	Direction coneNorm = direction_ / direction_.norm();

	// dot product of two normal vectors = cosine of angle
	// so angle = inverse of cos of this dot product
	double angle = acos(lightNorm.dot(direction_));
	// if angle > the half angle, angle_ then cut off the lighting
	if(angle > angle_) {
		return Colour(0,0,0);
	}

	// Decrease intensity with square of distance.
	double distance = (location_ - point).norm();
	if (distance < epsilon) distance = epsilon;
	return (1.0 / (distance*distance)) * colour_;
}

double SpotLightSource::getDistanceToLight(const Point& point) const {
	return (location_ - point).norm();
}

Direction SpotLightSource::getLightDirection(const Point& point) const {
	
	return point - location_;
}
