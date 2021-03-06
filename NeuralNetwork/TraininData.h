#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using std::string;
using std::vector;

class TrainingData
{
public:
	TrainingData(const std::string filename);
	bool isEof(void) { return m_trainingDataFile.eof(); }
	void getTopology(std::vector<int> &topology);

	// Returns the number of input values read from the file:
	unsigned getNextInputs(std::vector<double> &inputVals);
	unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

private:
	std::ifstream m_trainingDataFile;
};
