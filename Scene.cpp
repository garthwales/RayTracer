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

	for (const auto & light : lights_) {
		// Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
		} else{
			/************************************************** 
			 * TODO - ADD DIFFUSE AND SPECULAR LIGHTING HERE  *
			 *      - SHADOW COMPUTATIONS GO HERE ALSO        *
			 * ************************************************/
			
			// Find out if we are in a shadow, so don't calculte the rest of this.
			// Ray shadowRay;
			// shadowRay.point = hitPoint.point;
			// shadowRay.direction = light->getLightDirection(hitPoint.point);

			// bool inShade = false;
			// for (auto &obj : objects_) {
			// 	std::vector<RayIntersection> hits = obj->intersect(shadowRay);
			// 	for (auto &hit : hits) {
			// 		// also could add hit.distance > 0.0 && ...
			// 		if(hit.distance < light->getDistanceToLight(hitPoint.point)) {
			// 			inShade = true;
			// 			break;
			// 		}
			// 	}
			// }

			// if (inShade) {
			// 	continue;
			// }

			lightNorm = light->getLightDirection(hitPoint.point) / -light->getLightDirection(hitPoint.point).norm();

			// Calculate diffuse colour (Lambertian) from light source.
			// std::max to ensure we only add on the positive terms, otherwise it removes light when angle > 90 deg.
			// diffuseColour = hitPoint.material.diffuseColour * hitNorm.dot(lightNorm);
			diffuseColour = hitPoint.material.diffuseColour * std::max(hitNorm.dot(lightNorm),0.0);

			// Calculate the specular colour or something

			hitColour += light->getIlluminationAt(hitPoint.point) * (diffuseColour); // add specular into the brackets
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
