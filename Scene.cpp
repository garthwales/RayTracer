#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"

Scene::Scene() : backgroundColour(0,0,0), ambientLight(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);

	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5)*(2.0 / w);
			double cv = -h/w + (v + 0.5)*(2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;	
	for (const auto & obj : objects_) {
		for (const auto & hit : obj->intersect(ray)) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}	
	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(ray);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}

	Colour hitColour(0, 0, 0);
		
	/******************************************************************
	 * Code for better lighting, shadows, and reflections goes below. *
	 ******************************************************************/
	Normal hitNorm = hitPoint.normal / hitPoint.normal.norm();
	Colour diffuseColour;
	Direction lightNorm;

	Colour specularColour;
	Direction lightReflectedNorm;
	Direction viewNorm = -ray.direction / ray.direction.norm();

	Scene::intersect(ray);

	for (const auto & light : lights_) {
		// Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
		} else{
			/************************************************** 
			 * TODO - SPECULAR LIGHTING HERE  				  *
			 * ************************************************/
			
			// Find out if we are in a shadow, if so don't calculte the rest of this.
			Ray shadowRay;
			shadowRay.point = hitPoint.point;
			shadowRay.direction = -light->getLightDirection(hitPoint.point); //negative else shadows dont work :)
			if(intersect(shadowRay).distance < light->getDistanceToLight(hitPoint.point)) {
				continue;
			}

			// Have to put a negative, otherwise lighting is opposite 
			// (left to right instead of right to left for intensity given a right sided light)
			lightNorm = -light->getLightDirection(hitPoint.point);
			lightNorm /= light->getLightDirection(hitPoint.point).norm();

			// Calculate diffuse colour (Lambertian) from light source.
			// std::max to ensure we only add on the positive terms, otherwise it removes light when angle > 90 deg.
			// diffuseColour = hitPoint.material.diffuseColour * hitNorm.dot(lightNorm);
			diffuseColour = hitPoint.material.diffuseColour * std::max(hitNorm.dot(lightNorm),0.0);

			// Calculate the specular colour or something
			// r hat = 2(l.n)n-l
			lightReflectedNorm = 2 * lightNorm.dot(hitNorm) * hitNorm - lightNorm;
			lightReflectedNorm /= lightReflectedNorm.norm();

			specularColour = hitPoint.material.specularColour * std::pow(
								std::max(viewNorm.dot(lightReflectedNorm), 0.0)
								, hitPoint.material.specularExponent);


			hitColour += light->getIlluminationAt(hitPoint.point) * (diffuseColour + specularColour);
		}
	}

	/**********************************
	* TODO - ADD MIRROR EFFECTS HERE *
	**********************************/

	hitColour.clip();
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}
