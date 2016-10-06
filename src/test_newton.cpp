//
//  test_newton.cpp
//  HPSCProject2
//
//  Created by Paul Herz on 9/22/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include <cmath>

#include "println.cpp"
#include "newton.cpp"

int main(int argc, const char * argv[]) {
	
	// Test the Newton's Method implementation in `newton.cpp`
	// and determine a root approximation for a given function
	// using its derivative with given tolerance and iteration limit.
	
	// For your tests, start with initial guesses of x_0 = {−3, 1, 2},
	// and solve the problem to tolerances of ε = {1E−1, 1E−5, 1E−9}
	// (i.e. 9 tests in total). All of these tests should set
	// show iterates to true and should allow a maximum of 50 iterations.
	
	Fcn f = [](double x) -> double {
		// (x^2)(x^2-x-6)
		double x2 = std::pow(x,2);
		return (x2*(x2-x-6));
	};
	
	
	Fcn df = [](double x) -> double {
		// x (4x^2 -3x -12)
		double x2 = std::pow(x,2);
		return (4*x2-3*x-12);
	};
	
	size_t iterationLimit = 50;
	
	for(double initialGuess: {-3, 1, 2}) {
		for(double tolerance: {1.e-1, 1.e-5, 1.e-9}) {
			println("• Initial guess",initialGuess);
			println("• Tolerance",tolerance);
			double x = newton(f, df, initialGuess, iterationLimit, tolerance, true);
			println("The approximate root is", x);
			println("\n\n\n");
		}
	}
	
	return 0;
}
