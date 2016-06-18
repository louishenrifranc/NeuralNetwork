#include "Net.h"
#include "TraininData.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

/*
ofstream out("test.out");
out << "topology: 2 4 1" <<  endl;
for (int i(0); i < 10000; ++i)
{
double  a = (rand() & 1 ? 1.0 : 0.0);
double b = (rand() & 1 ? 1.0 : 0.0);
out << "in: " << (a == 1 ? "1.0" : "0.0") << " " << (b == 1 ? "1.0" : "0.0") << endl;
if ((int)(a) ^ (int)(b))
out << "out: " << "1.0" << endl;
else
out << "out: " << "0.0" << endl;

}
out.close();
*/
int main()
{
	TrainingData trainData("test.out");

	// e.g., { 3, 2, 1 }
	vector<int> topology;
	trainData.getTopology(topology);

	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	while (!trainData.isEof()) {
		++trainingPass;
		cout << endl << "Pass " << trainingPass;

		// Get new input data and feed it forward:
		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		cout << ": Inputs:" <<  inputVals[0] << " " << inputVals[1] << endl;
		myNet.feedForward(inputVals);

		// Collect the net's actual output results:
		myNet.getResults(resultVals);
		cout << "Outputs:" <<  resultVals[0] << " "  << endl;

		// Train the net what the outputs should have been:
		trainData.getTargetOutputs(targetVals);
		cout << "Targets:" <<  targetVals[0] << endl;
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Report how well the training is working, average over recent samples:
		//cout << "Net recent average error: "
			//<< myNet.getRecentAverageError() << endl;
	}

	cout << endl << "Done" << endl;
	system("pause");
	return 0;
}