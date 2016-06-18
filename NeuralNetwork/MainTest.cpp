#include "Net.h"
#include "TraininData.h"
#include <fstream>
using namespace std;

int main()
{
	ofstream out("test.out");
	out << "topology: 2 4 1" <<  endl;
	for (int i(0); i < 10000; ++i)
	{
		double  a = (rand() & 1 ? 1.0 : 0.0);
		double b = (rand() & 1 ? 1.0 : 0.0);
		out << "in: " << a << " " << b << endl;
		if ((int)(a) ^ (int)(b))
			out << "out: " << "1.0" << endl;
		else
			out << "out: " << "0.0" << endl;

	}
	out.close();
	return 0;
}