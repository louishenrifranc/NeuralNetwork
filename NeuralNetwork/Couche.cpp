#include "stdafx.h"
#include "Couche.h"


Couche::Couche(const int& n, const int& m, const int& nn) { 
	A.resize(n + 1, m); 
	A.col(1) = 1.0;  
	W.resize(nn + 1, n + 1); 
};
