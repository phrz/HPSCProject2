//
//  kepler.cpp
//  HPSCProject2
//
//  Created by Paul Herz on 10/3/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include <cmath>
#include <vector>
#include "println.cpp"
#include "Vector.h"
#include "newton.cpp"

using namespace PH;

// Kepler's equation:
//
//     ε sin(ω) - ω = t
//
// Where:
// • ε = sqrt(1 - b^2 / a^2) [orbital eccentricity]
// • t is proportional to time
// • ω is the angle of the object about its elliptical orbit

double eccentricity(double a, double b) {
	return std::sqrt( 1 - std::pow(b,2) / std::pow(a,2) );
}

// nonlinear root-finding function to solve
// Kepler's for ω
double f(double ω, double t, double ε) {
	//  0 = t - ε sin(ω) + ω
	return (t - (ε * sin(ω)) + ω);
}

double f1(double ω, double ε) {
	//  0 = -ε cos(ω)
	return (-1.0 * ε * cos(ω));
}

int main(int argc, const char * argv[]) {
	
	// Given values
	double a = 2.0;
	double b = 1.25;
	double ε = eccentricity(a, b);
	
	std::vector<double> newtonResults;
	
	// For each time t = {0, 0.001, ... , 10}:
	auto tSpace = Vector::linSpace(0, 10, 10000);
	
	tSpace.mapElements([&](double t, double tSpaceIndex){
		
		// • use Newton's method to solve Kepler's equation
		//   for ω(t). Tolerance 1e-5, max 6 iterations,
		//   no output. Guess should be previous solution or
		//   initially zero. (no global variables)
		
		double guess = 0;
		
		// Unary versions of f() and f'() for compatibility
		// with newton(), which expects (double)->double.
		
		auto  _f = [&](double ω){ return f(ω,t,ε); };
		auto _f1 = [&](double ω){ return f1(ω,ε); };
		
		guess = newton(_f, _f1, guess, 6, false);
		
	});
	
//	using Fcn = std::function<double(double)>;
//	
//	double newton(
//				  Fcn& f,
//				  Fcn& df,
//				  double x,
//				  size_t maxit,
//				  double tol,
//				  bool show_iterates)
	
	// • use the formula for radial position of an object
	//   at angle ω to compute cartesian coordinates
	//   x(t) = r cos(ω) and y(t) = r sin(ω).
	
	// • store the sets t, x(t), y(t), then export them.
}
