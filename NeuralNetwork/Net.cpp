#include "stdafx.h"
#include "Net.h"


Net::Net(const std::vector<int>& topology) {
	
	// Create 'topology.size' layers
	size_t numLayers = topology.size();
	
	// For all news layers
	for (size_t layerNum = 0; layerNum < numLayers; ++layerNum) {
		
		// Add a new layer
		layers.push_back(Layer());
		
		// Get the size of the next layer, used to create neurons that have numOuputs Connections
		size_t numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];


		// We have a new layer, now fill it with neurons, and
		// add a bias neuron in each layer.
		for (size_t neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			// Add Neuronof neuroNums size
			layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
		layers.back().back().setOutputVal(1.0);
	}
}





void Net::feedForward(const std::vector<double>& inputsVals)
{
	assert(inputsVals.size() == layers[0].size()-1);

	// Feed the first layers with input values
	for (size_t i = 0; i < inputsVals.size(); ++i)
		layers[0][i].setOutputVal(inputsVals[i]);

	// Forward propagation
	for (size_t layerNum = 1; layerNum < layers.size(); ++layerNum) {

		std::shared_ptr<Layer> previousLayers = std::make_shared<Layer>(layers[layerNum - 1]);
			for (size_t n = 0; n < layers[layerNum].size() - 1; ++n)
				layers[layerNum][n].feedForward(previousLayers);
	}
}

// BackPropagate 
void Net::backProp(const std::vector<double>& output) {
	
	smc = 0.0;
	for (int i(0); i < output.size() ; ++i)
	{
		double theta = output[i] - layers.back()[i].getOutputVal();
		smc += theta*theta;
	}

	smc /= (output.size());

	smc = std::sqrt(smc);

	// Gradient of output layer
	for (int i(0); i < output.size() ; ++i)
	{
		layers.back()[i].calcOutputGradient(output[i]);
	}

	// Calculate intemediate gradient
	for (int i(layers.size() - 2); i > 0; --i)
	{
		Layer& currentLayer = layers[i];
		Layer& nextLayer = layers[i + 1];

		for (int n(0); n < currentLayer.size() ; ++n) {
			currentLayer[n].calcHiddenGradient(nextLayer);
		}
	}

	// Update weight based on Gradient Descent
	for (int i(layers.size() - 1); i > 0; --i) {
		Layer& currentLayer = layers[i];
		Layer& previousLayer = layers[i - 1];

		for (int n(0); n < currentLayer.size() - 1; n++) {
			currentLayer[n].updateInputWeight(previousLayer);
		}
	}

}


void Net::getResults(std::vector<double>& results) const {
	results.clear();

	for (int i(0); i < layers.back().size() - 1; i++)
		results.emplace_back(layers.back()[i].getOutputVal());
		
}
