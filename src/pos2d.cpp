/*
 * pos2d.cpp
 *
 * Implementation of the positional 2 dimensional vector class that
 * includes the mathematics for periodic boundary conditions.
 *
 *  Created on: 10 Mar 2020
 *      Author: Tim Spain
 */

#include <ctgmath>
#include <iostream>

#include "dir2d.hpp"
#include "pos2d.hpp"

// Move in a given direction from this position
pos2d pos2d::operator+(dir2d &b){
	return this->displace(b);
}

dir2d pos2d::operator-(pos2d &b) {
	return pos2d::direction(b, *this);
}

double pos2d::distance(pos2d &b) {
	dir2d d = this->direction(b);
	return sqrt(d.x() * d.x() + d.y() * d.y());
}

// direction vector a - b, where 'this' is a
dir2d pos2d::direction(pos2d& b) {
	return direction(*this, b);
}

// direction vector from a to b
dir2d pos2d::direction(pos2d &a, pos2d &b) {
	double dx = b.x() - a.x();
	double dy = b.y() - a.y();
	if (fabs(dx) > x_wrap/2) {
		dx -= copysign(x_wrap, dx);
	}
	if (fabs(dy) > y_wrap/2) {
		dy -= copysign(y_wrap, dy);
	}
	return dir2d(dx, dy);
}

pos2d pos2d::displace(dir2d &b) {
	double nx = fmodulo(x() + b.x(), x_wrap);
	double ny = fmodulo(y() + b.y(), y_wrap);
	return pos2d(nx, ny);
}
