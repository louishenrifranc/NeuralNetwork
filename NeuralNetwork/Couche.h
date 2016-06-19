#pragma once
#include <armadillo>
class Couche
{
public:
	Couche(const int& n, const int& m, const int& nn);

	// Layer
	arma::mat A; 
	// Output weights
	arma::mat W
	// double *(functionPtr)()
};

