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

Fcn f = [](double x) -> double {
	// 10 + x^3 - 12*cos(x)
	return (10.0 + std::pow(x,3.0) - 12.0 * cos(x));
};


Fcn df = [](double x) -> double {
	// 3x^2 + 12*sin(x)
	return (3*std::pow(x,2) + 12*sin(x));
};

int main(int argc, const char * argv[]) {
	
	// Test the Newton's Method implementation in `newton.cpp`
	// and determine a root approximation for a given function
	// using its derivative with given tolerance and iteration limit.
	
	size_t maxit = 1000000;
	double tol = 1e-5;
	
//	double x = bisection(f, a, b, maxit, tol, true);
	double x_0 = 1;
	double x = newton(f, df, x_0, maxit, tol, true);
	
	println("The approximate root is", x);
	
	return 0;
}
