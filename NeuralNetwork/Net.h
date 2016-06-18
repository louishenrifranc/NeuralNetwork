#pragma once
#include <vector>
#include <cassert>
#include <memory>
#include "Neuron.h"


// A Neural Network
class Net {
public:

	//! Default Constructor
	//! @param vector<int> : topology of the network
	Net(const std::vector<int>&);

	//! feedforward the 
	//! @param vector<double> inputsVals
	void feedForward(const std::vector<double>&);

	// backpropagate the 
	// @param output values
	void backProp(const std::vector<double>&);

	// get the outputs results int the
	// @param vector<double>
	void getResults(std::vector<double>&) const;
private:

	using Layer = std::vector<Neuron>;

	// All Layers
	std::vector<Layer> layers;

	// Squared Mean Error
	// Used in the last layer
	double smc;

};
