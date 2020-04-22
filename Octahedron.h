#pragma once

#ifndef OCTAHEDRON_H_INCLUDED
#define OCTAHEDRON_H_INCLUDED

#include "Object.h"

/**
 * \file
 * \brief Octahedron class header file.
 */


 /**
  * \brief Class for Octahedron objects.
  *
  * This class provides an Object which is an Octahedron centred at the origin with "radius" 1.
  * That is, an Octahedron with vertices at \f$\pm1\f$ along each axis, as illustrated below:
  * 
  * \image html octahedron.png
  * 
  * Note that the Octahedron provided in the skeleton code is not complete and returns no
  * RayIntersection%s from intersect(). This method needs to be implemented correctly
  * as part of the assignment.
  *
  */
class Octahedron : public Object {

public:

	/** \brief Octahedron default constructor.
	 *
	 * A newly constructed Octahedron is centred at the origin, and extends 1 unit
	 * along each axis, with its vertices on the axes.
	 * It may be moved, rotated, and scaled through its transform member.
	 */
	Octahedron();

	/** \brief Octahedron copy constructor.
	 * \param octahedron The Octahedron to copy.
	 */
	Octahedron(const Octahedron& octahedron);

	/** \brief Octahedron destructor. */
	~Octahedron();

	/** \brief Octahedron assignment operator.
	 *
	 * \param octahedron The Octahedron to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	Octahedron& operator=(const Octahedron& octahedron);

	/** \brief Octahedron-Ray intersection computation.
	 *
	 * \todo The Cube-Ray intersection needs to be implemented as part of the assignment. 
	 *
	 * The intersection of a Ray with an Octahedron can be approached in a few ways.
	 * The basic constraint for a point on the surface of the base Octahedron is 
	 * \f$|x| + |y| + |z| = 1\f$.
	 * A simple, but not very elegant, way to approach this is to consider the eight
	 * faces independently, and intersect the ray with each of them in turn. 
	 * For example, the face with negative \f$Z\f$- and positive \f$X\f$- and 
	 * \f$Y\f$-values is defined by \f$ x + y - z = 1\f$.
	 *
	 * \param ray The Ray to intersect with this Octahedron.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // OCTAHEDRON_H_INCLUDED