#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;
/*
int main()
{
	mat A = randu<mat>(4, 5);
	mat B = randu<mat>(4, 5);
	
	mat C = ones<mat>(4,5);


	cout << A << endl;
	cout << A*B.t() << endl;
	cout << A.row(1) << endl;
	cout << A.col(1) << endl;
	cout << A(1,0) << endl;

	// Add 1 everywhere
	A++;
	cout << A << endl;
	// Element wise multiplication
	cout << A % B << endl;

	A = randn(2, 3);
	cout << A << endl;

	system("pause");
	return 0;
}


ones	 	generate object filled with ones
randi	 	generate object with random integer values in specified interval
randu / randn	 	generate object with random values (uniform and normal distributions)

A.transform( [](double val) { return (val + 123.0); } );
*/