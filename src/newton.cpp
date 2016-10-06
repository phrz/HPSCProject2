//
//  newton.cpp
//  HPSCProject2
//
//  Created by Paul Herz on 9/22/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include "println.cpp"
#include <cmath>

using Fcn = std::function<double(double)>;

double newton(
	Fcn& f,
	Fcn& df,
	double x,
	size_t maxit,
	double tol,
	bool show_iterates)
{
	// approximate the root of a provided function to a specified tolerance
	// using Newton's Method.
	
	// Def. Newton's Method
	//
	//     x_n+1 = x_n - f(x_n) / df(x_n)
	
	double previous = x;
	
	for(size_t i = 0; i < maxit; ++i) {
		
		if(show_iterates) {
			println("iteration",i,":");
			println("      x =",x);
			println("    |h| =", std::abs(previous-x));
			println(" |f(x)| =", f(x));
		}
		
		// if within tolerance, end iteration.
		if(tol > std::abs(f(x)/df(x))) {
			break;
		}
		
		previous = x;
		x = x - (f(x)/df(x));
	}
	
	return x;
}
