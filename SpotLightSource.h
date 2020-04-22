#pragma once

#ifndef SPOT_LIGHT_SOURCE_H_INCLUDED
#define SPOT_LIGHT_SOURCE_H_INCLUDED

#include "LightSource.h"
#include "Direction.h"

/**
 * \file 
 * \brief SpotLightSource class header file.
 */

/**
 * \brief Light emitted from a Point in a limited range of Directions.
 *
 * A SpotLightSource represents light emitted from a point in the Scene,
 * but which only illuminates in a cone.
 * The amount of light that reaches any given part of the scene should follow
 * a \f$1/r^2\f$ law, so more distant Objects receive less illumination, much like PointLightSource.
 * However, a SpotLightSource also has a Direction, and an angle property. 
 * Only objects that are within the specified angle of the SpotLightSource's Direction should be illuminated.
 *
 * This creates the effect of a cone of light, as shown in the illustration below. A SpotLightSource
 * at some location, \b p, illuminates a cone around the direction, \b d. Only the parts of an object 
 * within some angle \f$\theta\f$ of that direction are illuminated. There is no illumination from
 * the SpotLightSource outside of the cone (black shading in the illustration). Note that within the
 * cone parts of an Object can still be shadowed (grey shading) like any other LightSource.
 *
 * \image html spotLight.png
 */
class SpotLightSource : public LightSource {

public:


	/** \brief SpotLightSource constructor. 
	 *
     * Creates a new SpotLightSource.
	 * 
	 * \param colour The Colour of light emitted by the SpotLightSource.
	 * \param location The Location of the SpotLightSource.
	 * \param direction The Direction of the SpotLightSource.
	 * \param angle The half-angle of the cone of light emitted by the SpotLightSource
	 **/
	SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle);

	/** \brief SpotLightSource copy constructor. 
	 *
	 * \param lightSource The SpotLightSource to copy to \c this.
	 **/
	SpotLightSource(const SpotLightSource& lightSource);
	
	/** \brief SpotLightSource destructor */
	~SpotLightSource();
	
	/** \brief SpotLightSource assignment operator.
	 *
	 * \param lightSource The SpotLightSource to copy to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 **/
	SpotLightSource& operator=(const SpotLightSource& lightSource);

	/** \brief Determine how much light reaches a Point from this SpotLightSource.
	 *
	 * \todo The SpotLightSource intensity method needs to be implemented as part of the assignment.
	 *
	 * The illumination from a SpotLightSource should be the same as that from a PointLightSource
	 * within the angle of illumination, but zero outside of this cone.
	 *
	 * \param point The Point at which light is measured.
	 * \return The illumination that reaches the Point.
	 */
	Colour getIlluminationAt(const Point& point) const;
	
	/**
	 * \brief Determine how far away the light source is from a given Point.
	 *
	 * \return The distance between this light source and the point.
	 * \sa getDirectionToLight()
	 */
	double getDistanceToLight(const Point& point) const;


	/** \brief Direction from light source to a point.
	 *
	 * Return a Direction pointing from the given point towards the light source.
	 *
	 * \param point The point where the ray is being computed.
	 * \return The Direction from the point towards the light.
	 * \sa getDistanceToLight()
	 */
	Direction getLightDirection(const Point& point) const;

private:

	Point location_;      //!< The location of the SpotLightSource
	Direction direction_; //!< The direction of the SpotLightSource.
	double angle_;        //!< The half-angle, in degrees, of illumination provided by the SpotLightSource.

};

#endif