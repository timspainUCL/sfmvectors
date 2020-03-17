/*
 * pos2d.hpp
 *
 *  Created on: 6 Mar 2020
 *      Author: Tim Spain
 */

#ifndef SRC_POS2D_HPP_
#define SRC_POS2D_HPP_

#ifndef POS2D_XWRAP
#define POS2D_XWRAP 80.
#endif

#ifndef POS2D_YWRAP
#define POS2D_YWRAP 24.
#endif

#include <ctgmath>

#include "vec2d.hpp"
#include "dir2d.hpp"

class dir2d;

class pos2d : public vec2d {
private:
	static constexpr double x_wrap = POS2D_XWRAP;
	static constexpr double y_wrap = POS2D_YWRAP;

	double fmodulo(double x, double q) {
		double osign = copysign(1.0, q);
		double qa = osign * q;
		double xa = osign * x;
		double q2 = 0.5*qa;

		double f = fmod(xa, qa) + q2 - copysign(q2, xa);
		return osign * f;
	}

public:
	pos2d(double x, double y)
	: vec2d(fmodulo(x, x_wrap), fmodulo(y, y_wrap)) {};
	pos2d( )  // position at the origin
	: vec2d(0., 0.) {};
	pos2d operator+(dir2d &b);  // Move in a given direction from this position
	dir2d operator-(pos2d &b); // direction vector from there to here a-b, 'this' is a
	double distance(pos2d &); // distance between two positions
	dir2d direction(pos2d &b); // direction vector of b from 'this'
	pos2d displace(dir2d&); // position in the given direction from this initial position

	static double get_x_wrap() {return x_wrap;};
	static double get_y_wrap() {return y_wrap;};

	static dir2d direction(pos2d &a, pos2d &b); // direction vector from a to b
};



#endif /* SRC_POS2D_HPP_ */
