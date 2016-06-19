#include <vector>
#include <armadillo>
using namespace std;
using namespace arma;


int main()
{
	arma::mat A = randu<mat>(4, 5);
	arma::mat B = shuffle(A);
	cout << A << endl;
	cout << B << endl;
	system("pause");
}