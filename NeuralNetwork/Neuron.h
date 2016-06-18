#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Connection.h"

class Neuron {
public:
	Neuron(const size_t&, const size_t&);


	using Layer = std::vector<Neuron>;

	
	void setOutputVal(const double&);
	
	double getOutputVal() const;
	
	void feedForward(std::shared_ptr<Layer>&);

	void calcOutputGradient(const double&);

	void calcHiddenGradient(const Layer&);
	
	void updateInputWeight(Layer&);

	std::vector<Connection> weights;
private:
	const double eta = 0.15; // [0.0....1.0] overall net training rate
	const double alpha = 0.5; // [0.0 .. n] multiplier of the gradient change

	static double Sigmoid(const double&);
	static double inverseSigmoid(const double&);

	static double randomWeight();
	double output_val;

	double m_gradient;
	size_t my_index;
};