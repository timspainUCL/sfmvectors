/*
 * dirtest.cpp
 *
 *  Created on: 13 Mar 2020
 *      Author: Tim Spain
 *
 * Test the implementation of the direction class dir2d
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include "../src/pos2d.hpp"
#include "../src/dir2d.hpp"

#include <cmath>

double mean_reldiff(double a, double b) {
	if ((a == 0.) && (b == 0.))
			return 0.;
	return (b - a)/(0.5 * (b + a));
}

bool closely_equal(vec2d &a, vec2d &b) {
	const double tol = 1e-16; // tolerance for floating point comparisons
	return (abs(mean_reldiff(a.x(), b.x())) < tol)
				&& (abs(mean_reldiff(a.y(), b.y())) < tol);
}

TEST_CASE("Test closely equal", "[Tests]") {
	dir2d z1(0.,0.);
	dir2d z2(0.,0.);
	REQUIRE(closely_equal(z1, z2));
	dir2d d1(3, 2);
	dir2d d2(1, 0);
	REQUIRE(!closely_equal(d1, d2));

}

bool pos2d_addition_operator_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	pos2d xy2(x2, y2);
	pos2d xyt(xt, yt);

	pos2d xyr = xy1 + xy2;
	return closely_equal(xyr, xyt);
}

TEST_CASE("Test the addition overload with pos2d, including wrapping", "[Tests]") {
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			1, 1,
			3, 2));
	// Wrapping in x
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			4, 1,
			1, 2));
	// Wrapping in y
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			1, 2.5,
			3, 0.5));
	//Wrapping in both
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			4, 2.5,
			1, 0.5));
}

bool dir2d_addition_operator_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1 + xy2;
	return closely_equal(xyr, xyt);
}

TEST_CASE("Test the vector addition overload", "[Tests]") {
	REQUIRE(dir2d_addition_operator_test(
			2, 1,
			1, 1,
			3, 2));
	REQUIRE(dir2d_addition_operator_test(
			2, 1,
			4, 1,
			6, 2));
	REQUIRE(dir2d_addition_operator_test(
			2, 1,
			1, 2.5,
			3, 3.5));
	REQUIRE(dir2d_addition_operator_test(
			2, 1,
			4, 2.5,
			6, 3.5));
}

bool dir2d_subtraction_operator_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1 - xy2;
	return closely_equal(xyr, xyt);
}

TEST_CASE("Test the vector subtraction overload", "[Tests]") {
	REQUIRE(dir2d_subtraction_operator_test(
			2, 1,
			1, 1,
			1, 0));
	REQUIRE(dir2d_subtraction_operator_test(
			2, 1,
			4, 1,
			-2, 0));
	REQUIRE(dir2d_subtraction_operator_test(
			2, 1,
			1, 2.5,
			1, -1.5));
	REQUIRE(dir2d_subtraction_operator_test(
			2, 1,
			4, 2.5,
			-2, -1.5));
}

bool dir2d_multiplication_operator_test(
		double x1, double y1,
		double x2, double y2,
		double st) {
	dir2d xy1(x1, y1);
	dir2d xy2(x2, y2);

	double sr = xy1 * xy2;
	return mean_reldiff(st, sr) < 1e-16;
}

TEST_CASE("Test the scalar product multiplication overload", "[Tests]") {
	REQUIRE(dir2d_multiplication_operator_test(
			2, 1,
			1, 1,
			3));
	REQUIRE(dir2d_multiplication_operator_test(
			2, 1,
			-4, 1,
			-7));
	REQUIRE(dir2d_multiplication_operator_test(
			2, 1,
			1, -2.5,
			-0.5));
	REQUIRE(dir2d_multiplication_operator_test(
			-2, -1,
			4, 2.5,
			-10.5));
}

bool dir2d_negation_test(double x1, double y1) {
	dir2d xy1(x1, y1);
	dir2d xyt(-x1, -y1);
	dir2d xyn = -xy1;

	return closely_equal(xyn, xyt);
}
TEST_CASE("Test negation operator overloading", "[Tests]") {
	REQUIRE(dir2d_negation_test(0,0));
	REQUIRE(dir2d_negation_test(1,5));
}



bool pos2d_displacement_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	pos2d xy2(x2, y2);
	pos2d xyt(xt, yt);

	pos2d xyr = xy1.displace(xy2);
	return closely_equal(xyr, xyt);
}
TEST_CASE("pos2d displacement testing", "[Tests]") {
	REQUIRE(pos2d_addition_operator_test(
			2.5, 0.5,
			1, 1,
			3.5, 1.5));
	// Wrapping in x
	REQUIRE(pos2d_addition_operator_test(
			2.5, 1,
			3.5, 1,
			1, 2));
	// Wrapping in y
	REQUIRE(pos2d_addition_operator_test(
			2, 2.5,
			1, 2.5,
			3, 2));
	//Wrapping in both
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			4, 2.5,
			1, 0.5));
	// Negative and wrapping
	REQUIRE(pos2d_addition_operator_test(
			2, 1,
			-4, -2.5,
			3, 1.5));
}

bool dir2d_addition_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1.add(xy2);
	return closely_equal(xyr, xyt);
}

TEST_CASE("Test vector addition", "[Tests]") {
	REQUIRE(dir2d_addition_test(
			2, 1,
			1, 1,
			3, 2));
	REQUIRE(dir2d_addition_test(
			2, 1,
			4, 1,
			6, 2));
	REQUIRE(dir2d_addition_test(
			2, 1,
			1, 2.5,
			3, 3.5));
	REQUIRE(dir2d_addition_test(
			2, 1,
			4, 2.5,
			6, 3.5));
	REQUIRE(dir2d_addition_test(
			3, 1,
			-2.5, -3.5,
			0.5, -2.5));
}

bool dir2d_subtraction_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	dir2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1.subtract(xy2);
	return closely_equal(xyr, xyt);
}

TEST_CASE("Test vector subtraction", "[Tests]") {
	REQUIRE(dir2d_subtraction_test(
			2, 1,
			1, 1,
			1, 0));
	REQUIRE(dir2d_subtraction_test(
			2, 1,
			4, 1,
			-2, 0));
	REQUIRE(dir2d_subtraction_test(
			2, 1,
			1, 2.5,
			1, -1.5));
	REQUIRE(dir2d_subtraction_test(
			2, 1,
			4, 2.5,
			-2, -1.5));
	REQUIRE(dir2d_subtraction_test(
			3, 1,
			-2.5, -3.5,
			5.5, 4.5));

}

bool dir2d_length_test(double x1, double y1, double l) {
	double lr = dir2d(x1, y1).length();
	return abs(mean_reldiff(lr, l)) < 1e-16;
}
TEST_CASE("Test vector length", "[Tests]") {
	REQUIRE(dir2d_length_test(0., 0., 0.));
	REQUIRE(!dir2d_length_test(1., 1., 2.));
	REQUIRE(dir2d_length_test(3., 4., 5.));
}

bool dir2d_cosangle_test(
		double x1, double y1,
		double x2, double y2,
		double cosangle) {
	dir2d xy1 = dir2d(x1, y1);
	dir2d xy2 = dir2d(x2, y2);
	double cosr = xy1.cos_angle(xy2);

	return abs(mean_reldiff(cosr, cosangle)) < 3e-16; // extra leeway for the parallel case
}
TEST_CASE("Test cos angle calculation") {
	REQUIRE(dir2d_cosangle_test(
			1, 1,
			1, 1,
			1));
	double sqrt2 = sqrt(2.);
	REQUIRE(dir2d_cosangle_test(
			1, 0,
			1, 1,
			sqrt2/2));
	double cos345 = 4./5.;
	REQUIRE(dir2d_cosangle_test(
			4, 0,
			4, 3,
			cos345));
	REQUIRE(!dir2d_cosangle_test(
			4, 0,
			4, 3,
			sqrt2));
}

TEST_CASE("Test in-place negation", "[Tests]") {
	double x1 = 1;
	double y1 = 5;
	dir2d xy1(x1, y1);
	xy1.negate();
	REQUIRE(xy1.x() == -x1);
	REQUIRE(xy1.y() == -y1);
}

TEST_CASE("Test negation", "[Tests]") {
	double x1 = 1;
	double y1 = 5;
	dir2d xy1(x1, y1);
	dir2d xyn = xy1.negative();
	REQUIRE(xyn.x() == -x1);
	REQUIRE(xyn.y() == -y1);
}

TEST_CASE("Test scalar multiplication base class", "[Tests]") {
	double x1 = 2.;
	double y1 = 3.;
	double s = 2.;

	vec2d xy1(x1, y1);
	vec2d xys(s*x1, s*y1);
	vec2d xyc = xy1 * s;

	REQUIRE(closely_equal(xyc, xys));
}

TEST_CASE("Test scalar multiplication inheritance", "[Tests]") {
	double x1 = 2.;
	double y1 = 3.;
	double s = 2.;

	dir2d xy1(x1, y1);
	dir2d xys(s*x1, s*y1);
	dir2d xyc = xy1 * s;
	dir2d xyd = s * xy1;

	REQUIRE(closely_equal(xyc, xys));
	REQUIRE(closely_equal(xyd, xys));
}
