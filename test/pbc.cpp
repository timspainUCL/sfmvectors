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
bool generic_addition_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt);
double mean_reldiff(double a, double b);

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
	double tol = 1e-16; // tolerance for floating point comparisons

	dir2d xyr = xy1.direction(xy2);
	return (mean_reldiff(xyr.x(), xyt.x()) < tol)
			&& (mean_reldiff(xyr.y(), xyt.y()) < tol);
}

double mean_reldiff(double a, double b) {
	return (b - a)/(0.5 * (b + a));
}

TEST_CASE("Addition test", "[Tests]") {
	// No wrapping
	REQUIRE(generic_addition_test(
			1, 1,
			2, 1,
			3, 2));
	// Wrapping in x
	REQUIRE(generic_addition_test(
			2, 1,
			4, 1,
			1, 2));
	// Wrapping in y
	REQUIRE(generic_addition_test(
			1, 1,
			2, 3,
			3, 1));
	// Wrapping in x and y
	REQUIRE(generic_addition_test(
			3, 2,
			3, 2,
			1, 1));
}

bool generic_addition_test(
		double x1, double y1,
		double x2, double y2,
		double xt, double yt) {
	pos2d xy1(x1, y1);
	dir2d xy2(x2, y2);
	pos2d xyt(xt, yt);
	double tol = 1e-16;

	pos2d xyr = xy1.displace(xy2);
	return (mean_reldiff(xyr.x(), xyt.x()) < tol)
			&& (mean_reldiff(xyr.y(), xyt.y()) < tol);

}
