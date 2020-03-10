/*
 * vec2d.hpp
 *
 *  Created on: 5 Mar 2020
 *      Author: Tim Spain
 */

#ifndef SRC_VEC2D_HPP_
#define SRC_VEC2D_HPP_

class vec2d {
private:
	double xx;
	double yy;
public:
	vec2d(double x, double y):
		xx(x), yy(y) { }
	vec2d operator+(vec2d &b); // vector addition
	vec2d operator-(vec2d &b); // vector subtraction
	double operator*(vec2d &b); // scalar product
	vec2d operator*(double &c)
	{return vec2d(c * xx, c * yy);} // scaling
	double operator[](int i) // Get first or second component
	{return i ? xx : yy;}
	double x() {return xx;} // Access the x component
	double y() {return yy;} // Access the y component
};

#endif /* SRC_VEC2D_HPP_ */
