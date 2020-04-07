/*
 * dir2d.hpp
 *
 *  Created on: 6 Mar 2020
 *      Author: Tim Spain
 */

#ifndef SRC_DIR2D_HPP_
#define SRC_DIR2D_HPP_

#include "vec2d.hpp"
#include "pos2d.hpp"

class pos2d;

class dir2d : public vec2d {
public:
	dir2d(double x, double y)
	: vec2d(x, y) { };
//	dir2d(vec2d&);

	pos2d operator+(pos2d&); // move the given position in this direction
	dir2d operator+(dir2d&); // vector addition
	dir2d operator-(dir2d &b); // vector subtraction
	double operator*(dir2d &b); // Scalar product between this and b
	dir2d operator*(double); // Scaling vector * scalar
	dir2d operator-(); // unary negation operator

	pos2d displace(pos2d&); // Move a position in this direction
	dir2d add(dir2d&); // vector addition
	dir2d subtract(dir2d &b); // vector subtraction
	double scalar_product(dir2d &b); // Scalar product between this and b
	double length(); // length of this direction vector
	double cos_angle(dir2d &b); // Cosine of the angle between this and b
	void negate(); // negative vector, in place
	dir2d negative(); // returns the negative vector, leaving the original
};

dir2d operator*(double, dir2d); // Scaling scalar * vector


#endif /* SRC_DIR2D_HPP_ */
