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

double r(double ω, double a, double b) {
	return ( (a*b) / sqrt( pow(b*cos(ω),2) + pow(a*sin(ω),2)) );
}

// nonlinear root-finding function to solve
// Kepler's for ω
double f(double ω, double t, double ε) {
	//  0 = ε sin(ω) - ω - t
	return ((ε * sin(ω)) - ω - t);
}

double f1(double ω, double ε) {
	//  0 = ε cos(ω) - 1
	return (ε * cos(ω) - 1.0);
}

int main(int argc, const char * argv[]) {
	
	// Given values
	double a = 2.0;
	double b = 1.25;
	double ε = eccentricity(a, b);
	double tolerance = 1.e-5;
	size_t maxIterations = 6;
	size_t timeSpaceSize = 10000;
	
	auto newtonResults = Vector(timeSpaceSize);
	auto x_t = Vector(timeSpaceSize);
	auto y_t = Vector(timeSpaceSize);
	
	// For each time t = {0, 0.001, ... , 10}:
	auto tSpace = Vector::linSpace(0, 10, timeSpaceSize);
	double guess = 0;
	tSpace.mapElements([&](double t, double index){
		
		// • use Newton's method to solve Kepler's equation
		//   for ω(t). Tolerance 1e-5, max 6 iterations,
		//   no output. Guess should be previous solution or
		//   initially zero. (no global variables)
		
		// Unary versions of f() and f'() for compatibility
		// with newton(), which expects (double)->double.
		
		Fcn  _f = [&](double ω){ return f(ω,t,ε); };
		Fcn _f1 = [&](double ω){ return f1(ω,ε); };
		
		double ω = newton(_f, _f1, guess, maxIterations, tolerance, false);
		guess = ω;
		newtonResults[index] = ω;
		
		// • use the formula for radial position of an object
		//   at angle ω to compute cartesian coordinates
		//   x(t) = r(ω) cos(ω) and y(t) = r(ω) sin(ω).
		
		double r_ω = r(ω, a, b);
		
		x_t[index] = r_ω * cos(ω);
		y_t[index] = r_ω * sin(ω);
		
	});
	
	// • store the sets t, x(t), y(t), then export them.
	
	std::string prefix = "../data/";
	tSpace.saveTo(prefix + "t.txt");
	x_t.saveTo(prefix + "x.txt");
	y_t.saveTo(prefix + "y.txt");
	
}
