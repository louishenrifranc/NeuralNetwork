#pragma once
#include <armadillo>


class ActivationFunction
{
public:
	ActivationFunction();
	~ActivationFunction();

	template<typename T>
	void activation(T& t);
};

