/*
 * dir2d.cpp
 *
 *  Created on: 13 Mar 2020
 *      Author: Tim Spain
 */

#include "dir2d.hpp"
#include "pos2d.hpp"
#include <cmath>

pos2d dir2d::operator+(pos2d &b) {
	return displace(b);
}

dir2d dir2d::operator+(dir2d &b) {
	return dir2d(x() + b.x(), y() + b.y());
}

dir2d dir2d::operator-(dir2d &b) {
	return dir2d(x() - b.x(), y() - b.y());
}

double dir2d::operator*(dir2d &b) {
	return x() * b.x() + y() * b.y();
}

dir2d dir2d::operator-() {
	return dir2d(-x(), -y());
}

pos2d dir2d::displace(pos2d &b) {
	return b.displace(*this);
}

dir2d dir2d::add(dir2d &b) {
	return *this + b;
}

dir2d dir2d::subtract(dir2d &b) {
	return *this - b;
}

double dir2d::scalar_product(dir2d &b) {
	return *this * b;
}

double dir2d::length() {
	return sqrt(scalar_product(*this));
}

double dir2d::cos_angle(dir2d &b) {
	return scalar_product(b)/(length() * b.length());
}

void dir2d::negate( ) {
	*this = this->negative();
}

dir2d dir2d::negative( ) {
	return dir2d(-x(), -y());
}
