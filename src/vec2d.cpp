/*
 * vec2.cpp
 *
 *  Created on: 5 Mar 2020
 *      Author: Tim Spain
 */

#include "vec2d.hpp"

vec2d::vec2d(double x, double y)
: xx(x), yy(y)
{ }

vec2d vec2d::operator+(vec2d &b) {
	return vec2d(xx + b.xx, yy + b.yy);
}

vec2d vec2d::operator-(vec2d &b) {
	return vec2d(xx - b.xx, yy - b.yy);
}

double vec2d::operator*(vec2d &b) {
	return xx * b.xx + yy * b.yy;
}

vec2d vec2d::operator*(double &c) {
	return vec2d(c * xx, c * yy);
}
