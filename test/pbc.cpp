/*
 * pbc.cpp
 *
 *  Created on: 9 Mar 2020
 *      Author: Tim Spain
 *
 * Test the periodic boundary conditions of the 2d vector classes.
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

// Define the size of the periodic boundary conditions for pos2d
#define POS2D_XWRAP 10.
#define POS2D_YWRAP 5.

#include "../src/pos2d.hpp"
#include "../src/dir2d.hpp"

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

TEST_CASE("Direction calculation", "[Tests]") {

	// The direction from (1,1) to (3,2) should be (2,1)
	REQUIRE(generic_direction_test(
			1, 1,
			3, 2,
			2, 1));

	// The direction from (1,1) to (4,2) should be (-2,1), due to the
	// wrap around in x
	REQUIRE(generic_direction_test(
			1, 1,
			4, 2,
			-2, 1));

	// The direction from (1, 0.5) to (3, 2.5) should be (2,-1), due
	// to the wrap around in y
	REQUIRE(generic_direction_test(
			1, 0.5,
			3, 2.5,
			2, -1));

	// The direction from (1, 0.5) to (4, 2.5) should be (-2,-1), due
	// to the wrap around in both x and y
	REQUIRE(generic_direction_test(
			1, 0.5,
			4, 2.5,
			-2, -1));

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
	return (b - a)/(0.5 * (b + a));
}

bool closely_equal(vec2d &a, vec2d &b) {
	const double tol = 1e-16; // tolerance for floating point comparisons
	return (mean_reldiff(a.x(), b.x()) < tol)
				&& (mean_reldiff(a.y(), b.y()) < tol);
}

TEST_CASE("Addition test", "[Tests]") {
	// No wrapping
	REQUIRE(generic_displacement_test(
			1, 1,
			2, 1,
			3, 2));
	// Wrapping in x
	REQUIRE(generic_displacement_test(
			2, 1,
			4, 1,
			1, 2));
	// Wrapping in y
	REQUIRE(generic_displacement_test(
			1, 1,
			2, 3,
			3, 1));
	// Wrapping in x and y
	REQUIRE(generic_displacement_test(
			3, 2,
			3, 2,
			1, 1));
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

	// The direction from (1,1) to (4,2) should be (-2,1), due to the
	// wrap around in x
	REQUIRE(generic_subtraction_test(
			4, 2,
			1, 1,
			-2, 1));

	// The direction from (1, 0.5) to (3, 2.5) should be (2,-1), due
	// to the wrap around in y
	REQUIRE(generic_subtraction_test(
			3, 2.5,
			1, 0.5,
			2, -1));

	// The direction from (1, 0.5) to (4, 2.5) should be (-2,-1), due
	// to the wrap around in both x and y
	REQUIRE(generic_subtraction_test(
			4, 2.5,
			1, 0.5,
			-2, -1));


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
	REQUIRE(generic_distance_test(
			1, 1,
			4, 2,
			5));
	REQUIRE(generic_distance_test(
			1, 0.5,
			3, 2.5,
			5));
	REQUIRE(generic_distance_test(
			1, 0.5,
			4 ,2.5,
			5));
	// Test a distance that isn't sqrt 5
	REQUIRE(generic_distance_test(
			4.5, 2.5,
			0.5, 0.5,
			2));
}
