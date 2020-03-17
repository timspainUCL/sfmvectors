/*
 * pbc.cpp
 *
 *  Created on: 16 Mar 2020
 *      Author: Tim Spain
 *
 * Test the periodic boundary conditions of the 2d vector classes.
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

// Do not define the size of the periodic boundary conditions for pos2d
// Let them default to 80x24

#include "../src/pos2d.hpp"
#include "../src/dir2d.hpp"

#include <cmath>

bool generic_direction_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt);
bool generic_displacement_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt);
double mean_reldiff(double a, double b);

bool closely_equal(vec2d &a, vec2d &b);

TEST_CASE("Test the wrap values", "[Tests]") {
	REQUIRE(pos2d::get_x_wrap() == POS2D_XWRAP);
	REQUIRE(pos2d::get_y_wrap() == POS2D_YWRAP);
}

bool ctor_test(double xin, double yin, double xt, double yt) {
	pos2d construct(xin, yin);
	pos2d target(xt, yt);
	return closely_equal(construct, target);
}

TEST_CASE("Test the constructor", "[Tests]") {
	// Centre of the field
	REQUIRE(ctor_test(40, 12, 40, 12));
	// Near the wrap-around
	REQUIRE(ctor_test(79, 23, 79, 23));
	// On the edge
	REQUIRE(ctor_test(80, 24, 0, 0));
	// Over the edge
	REQUIRE(ctor_test(81, 25, 1, 1));
	// Check the coordinates have genuinely wrapped
	pos2d p(6, 4);
	REQUIRE(p.x() == 6.);
	REQUIRE(p.y() == 4.);
	// Check the coordinates have genuinely wrapped
	pos2d q(86, 34);
	REQUIRE(q.x() != 86.);
	REQUIRE(q.y() != 34.);

}

TEST_CASE("Direction calculation", "[Tests]") {

	// The direction from (1,1) to (3,2) should be (2,1)
	REQUIRE(generic_direction_test(
			1, 1,
			3, 2,
			2, 1));

}

bool generic_direction_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	pos2d xy1(x1, y1);
	pos2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1.direction(xy2);
	return closely_equal(xyr, xyt);
}

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

TEST_CASE("Addition test", "[Tests]") {
	// No wrapping
	REQUIRE(generic_displacement_test(
			1, 1,
			2, 1,
			3, 2));
}

bool generic_displacement_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	pos2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	pos2d xyt(xt, yt);

	pos2d xyr = xy1.displace(xy2);
	return closely_equal(xyr, xyt);
}

bool generic_subtraction_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	pos2d xy1(x1, y1);
	pos2d xy2(x2, y2);
	dir2d xyt(xt, yt);

	dir2d xyr = xy1 - xy2;
	return closely_equal(xyr, xyt);
}

// Subtraction, operator-()
TEST_CASE("operator- tests", "[Tests]") {
	// The direction from (1,1) to (3,2) should be (2,1)
	REQUIRE(generic_subtraction_test(
			3, 2,
			1, 1,
			2, 1));

}

// Use distance squared for easier, more accurate data entry
bool generic_distance_test(
		double x1, double y1,
		double x2, double y2,
		double dt2) {
	pos2d xy1(x1, y1);
	pos2d xy2(x2, y2);

	double dr = xy1.distance(xy2);
	const double tol = 1e-16;
	return (mean_reldiff(dr, sqrt(dt2)) < tol);
}

TEST_CASE("Distance tests", "[Tests]") {
	REQUIRE(generic_distance_test(
			1, 1,
			3, 2,
			5));
}
