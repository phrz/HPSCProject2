//
//  vandermonde.cpp
//  HPSCProject2
//
//  Created by Paul Herz on 9/21/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include "Matrix.h"
#include "Vector.h"
#include "println.cpp"

using namespace PH;

Matrix makeVandermonde(Vector v) {
	// The Vandermonde matrix of order n is an (n,n) matrix is defined as
	// A(r,c) = v[r] ^ c (assuming zero indexing!)
	
	Matrix vandermonde = Matrix(v.size(), v.size());
	
	vandermonde.mapElements([&](double& element, Index r, Index c) {
		element = std::pow(v[r], c);
	});
	
	return vandermonde;
}

int main(int argc, const char * argv[]) {
	
	// Solve a linear system Ax=b with a Vandermonde A of order n
	// for each n = 5, 9, 17, 33, 65.
	for(auto n : {5, 9, 17, 33, 65}) {
		
		println("n =",n,":");
		
		// To generate the matrix, use vector v with an n-size linear span
		// 0...1 (inclusive), and vector x with n random entries.
		
		Vector v = Vector::linSpace(0, 1, n);
		Vector x = Vector::random(n);
		
		Matrix A = makeVandermonde(v);
		
		// Set b to be equal to A*x so the exact solution is known.
		
		Vector b = A*x;
		
		// find x-hat using the linear solver with A and b.
		
		try {
			// Copy A and b as they will be modified but we need
			// the originals for error calculation
			auto bTemp = Vector(b);
			auto ATemp = Matrix(A);
			Vector xHat = Matrix::linearSolve(ATemp, bTemp);
			
			// print the 2-norm of the error vector and the residual vector
			Vector errorVector = Vector(n);
			errorVector.mapElements([&](double& element, Index i) {
				element = std::abs( xHat[i] - x[i] );
			});
			
			Vector residualVector = b - (A * xHat);
			
			println("  • Error vector 2-norm:", Vector::norm(errorVector));
			println("  • Residual vector 2-norm:", Vector::norm(residualVector));
			
		} catch(std::runtime_error* e) {
			println("  • Matrix is singular");
		}
		
		println("-------------------------------");
		
	}
	
	// output can be piped to file with "binaryfile > outputfile"
	
	return 0;
}
