#pragma once
#include <vector>
#include <armadillo>
#include <algorithm>
#include "Couche.h"
using std::vector;
using std::pair;
using arma::mat;
class Net2 {
public:
	// vector for the topology (number of neuron in the layer and function used)
	// minibatch : the ratio for for mini batch
	// size_input : the size of dataset
	Net2(const vector<pair<int, int>>&, int size_input, int minibatch = 1);
	void fit(const mat&, const mat&);

	void feedforward(const mat&, const mat&);
private:
	int ratio_mini_batch;
	int number_of_samples;
	vector<Couche> layers;
};