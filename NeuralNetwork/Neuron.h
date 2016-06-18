#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Connection.h"

class Neuron {
public:
	using Layer = std::vector<Neuron>;


	// Create a Neuron that has 
	// @param1 numbers of connections (number of neurons in the next layer
	// @param2 the identifiant of the neuron in the layer
	Neuron(const size_t&, const size_t&);


	// The output value of the neuron
	void setOutputVal(const double&);
	

	// Get the output value
	double getOutputVal() const;
	

	// FeedForward the neuron with the previous weight.
	// @param shared_ptr<Layer> the previous Layer
	// Basically the operation is 
	//----------------------------------------------------------------------------------------------------------
	//          output_value = sum [on the neuron N in the previous layer of N.outputvalue * weight between N and this neuron]
	void feedForward(std::shared_ptr<Layer>&);

	//! Calculate the Output Gradient 
	//! It is used if the neuron is in the last layer, else no
	//! @param double : the supposed output value
	// Basically the operation is 
	//!----------------------------------------------------------------------------------------------------------
	//!        m_gradient = (supposed_value - value__outputed_by_the_NN)*derivative(value__outputed_by_the_NN)
	void calcOutputGradient(const double&);

	//! Calculate the Gradient if the Neuron is in an hidden layer (not the first layer which is an input layer)
	//! @param the next Layer in the order of the NN
	// Basically the operation is 
	//!----------------------------------------------------------------------------------------------------------
	//			gradient = sum [of all weights started at this neuron and ending in the neuron N of the nextlayer
	//												* N.m_gradient]
	//                                                      * derivative_of_function(output_value)
	void calcHiddenGradient(const Layer&);
	
	//! Update some weights on the /!\ previousLayer passed in parameter
	//! @param layer : the previous layer
	//! Update all the weights in the previous layer that are on a link to this neuron
	//! Also Update the accumulator
	//! Basically the operation is 
	//!----------------------------------------------------------------------------------------------------------
	//!			 all neuron PN in the previous layer :
	//				PN.accumulator_to_this_neuron = eta * PN.outputvalue * this.gradient + alpha * PN.accumulator_to_this_neuron
	//				PN.weight_to_this_neuron += PN.accumulator_to_this_neuron
	void updateInputWeight(Layer&);


	// The vector that keeps the weight and the accumulator for all link between this neuron and all neurons in the next layer
	std::vector<Connection> weights;
private:
	const double eta = 0.15; // [0.0....1.0] overall net training rate
	const double alpha = 0.5; // [0.0 .. n] multiplier of the gradient change

	// Sigmoid
	static double Sigmoid(const double&);
	// Tanh
	static double deriveeSigmoid(const double&);

	// Get a random weight
	static double randomWeight();
	
	// The output value of this neuron (often called a_i) i for this neuron
	double output_val;

	// The gradient of this neuron (often called sigma_i) i for this neuron
	double m_gradient;

	// The index of the neuron in the layer
	size_t my_index;
};