#include "stdafx.h"
#include "Neuron.h"


Neuron::Neuron(const size_t& size_next_layer, const size_t& my_index) :
	my_index(my_index)
{
	weights.resize(size_next_layer, Connection());
	std::for_each(weights.begin(), weights.end(), [](auto& connection) {
		connection.weigth = randomWeight();
	});
}




double Neuron::randomWeight()	{ 
	return rand() / double(RAND_MAX);
}

void Neuron::setOutputVal(const double& x) {
	output_val = x;
}

double Neuron::getOutputVal() const {
	return output_val;
}

void Neuron::feedForward(std::shared_ptr<Layer>& previous_layer) {

	double sum = 0.0;

	for (int i(0); i < previous_layer->size(); ++i) 
		sum += previous_layer->at(i).getOutputVal() 
				 * previous_layer->at(i).weights[my_index].weigth;
	
	output_val = Neuron::Sigmoid(sum);

}

double Neuron::Sigmoid(const double& ff)
{
	// return 1 / (1.0 + std::exp(ff));
	return std::tanh(ff);
}


double Neuron::deriveeSigmoid(const double& ff) {
	// return Sigmoid(ff)*(1 - Sigmoid(ff));
	return 1.0 - ff * ff;
}


void Neuron::calcOutputGradient(const double& supposed_value) {
	double theta = supposed_value - output_val;
	m_gradient = theta * Neuron::deriveeSigmoid(output_val);
}

void Neuron::calcHiddenGradient(const Layer& next_layer) {
	
	double gradient(0.0);
	for (int i(0); i < weights.size(); i++)
	{
		gradient += weights[i].weigth * next_layer.at(i).m_gradient;
	}

	gradient*= Neuron::deriveeSigmoid(output_val);
	
	m_gradient = gradient;
}

void Neuron::updateInputWeight(Layer& prevLayer)
{
	for (size_t n = 0; n < prevLayer.size(); ++n)
	{
		Neuron& neuron = prevLayer[n];

		double oldDeltaWeight = neuron.weights[my_index].gradient_weight;
		
		// It's the formula
		double newDeltaWeight =
			eta
			* neuron.getOutputVal()
			* m_gradient
			+ alpha
			* oldDeltaWeight;
		
		neuron.weights[my_index].gradient_weight = newDeltaWeight;
		neuron.weights[my_index].weigth += newDeltaWeight;
	}
}