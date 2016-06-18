#pragma once
#include <vector>
#include <cassert>
#include <memory>
#include "Neuron.h"

class Net {
public:
	// Default Constructor
	Net(const std::vector<int>&);

	// feedforward
	void feedForward(const std::vector<double>& inputVals);

	// backpropagate
	void backProp(const std::vector<double>&);

	void getResults(std::vector<double>& results) const;
private:
	using Layer = std::vector<Neuron>;

	// All Layers
	std::vector<Layer> layers;

	// somme des moindres carrés
	double smc;

};
