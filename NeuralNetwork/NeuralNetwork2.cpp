// NeuralNetwork.cpp : Defines the entry point for the console application.
//
/*
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>
#include <ctime>

struct Unit {
	Unit() = default;
	Unit(const double& a, const double& b) : val(a), grad(b) {};
	double val;
	double grad;
};

using ptr_Unit = std::shared_ptr<Unit>;

class Gate {
public:

	virtual ptr_Unit forward(ptr_Unit, ptr_Unit) = 0;

	virtual void backward() = 0;

	ptr_Unit a; // input unit
	ptr_Unit c; // output unit
};

class MultiplyGate : Gate
{
public:
	MultiplyGate() {};
	virtual ptr_Unit forward(ptr_Unit a_, ptr_Unit b_) override {
		a = a_;
		b = b_;
		c = std::make_shared<Unit>(a->val * b->val, 0.0);
		return c;
	}
	virtual void backward() override
	{
		a->grad += b->val * c->grad;
		b->grad += a->val * c->grad;
	}
	ptr_Unit b; // input unit

};

class AddGate : Gate
{
public:
	// AddGate() = default;
	virtual ptr_Unit forward(ptr_Unit a_, ptr_Unit b_) override
	{

		a = a_;
		b = b_;
		c = std::make_shared<Unit>(a->val + b->val, 0.0);
		return c;
	}
	virtual void backward() override {

		a->grad += c->grad;
		b->grad += c->grad;
	}
	ptr_Unit b; // input unit

};

class SigmoidGate : Gate
{
public:
	// SigmoidGate() = default;
	virtual ptr_Unit forward(ptr_Unit a_, ptr_Unit b_ = std::make_shared<Unit>(0.0, 0.0)) override
	{
		a = a_;
		c = std::make_shared<Unit>(sigmoid(a->val), 0.0);
		return c;
	}
	virtual void backward() override {
		a->grad += sigmoid(a->val)*(1 - sigmoid(a->val))* c->grad;
	}

	double sigmoid(double x)
	{
		return 1 / (static_cast<double>(1 + exp(-x)));
	};
};

class Circuit {
public:
	Circuit() : mulg1(), mulg2(), addg1(), addg2() {};

	ptr_Unit forward(ptr_Unit  x, ptr_Unit  y, ptr_Unit a, ptr_Unit  b, ptr_Unit c)
	{
		ax = mulg1.forward(a, x);
		by = mulg2.forward(b, y);
		axpby = addg1.forward(ax, by);
		axpbyc = addg2.forward(axpby, c);
		return axpbyc;
	}

	void backward(double gradient_top)
	{
		axpbyc->grad = gradient_top;
		addg2.backward(); addg1.backward(); mulg2.backward(); mulg1.backward();
	}

	MultiplyGate mulg1, mulg2;
	AddGate addg1, addg2;
	ptr_Unit ax, by, axpby, axpbyc;
};


class SVM
{
public:
	SVM() : a(std::make_shared<Unit>(0.0, 0.0)),
		b(std::make_shared<Unit>(0.0, 0.0)),
		c(std::make_shared<Unit>(0.0, 0.0)),
		circuit() {};
	ptr_Unit forward(ptr_Unit x, ptr_Unit y)
	{
		out = circuit.forward(x, y, a, b, c);
		return out;
	};

	void backward(int label)
	{
		a->grad = b->grad = c->grad = 0.0;
		auto pull = 0.0;
		if (label == 1 && out->val < 1)
			pull = 1;
		if (label == -1 && out->val > -1)
			pull = -1;
		circuit.backward(pull);
		// a->grad += -a->val;
		// b->grad += -b->val;
	}

	void learn(ptr_Unit x, ptr_Unit y, int label)
	{
		forward(x, y);
		backward(label);
		parameterUpdate();
	}

	void parameterUpdate()
	{
		auto step_size = 0.01;
		a->val += step_size * a->grad;
		b->val += step_size * b->grad;
		c->val += step_size * c->grad;
	}

public:
	ptr_Unit a, b, c, out;
	Circuit circuit;
};




int main()
{

	srand(time(NULL));

	std::vector<std::pair<double, double> > data;
	std::vector<int> labels;
	data.push_back(std::make_pair(1.2, 0.7)); labels.push_back(1);
	data.push_back(std::make_pair(-0.3, -0.5)); labels.push_back(-1);
	data.push_back(std::make_pair(3.0, 0.1)); labels.push_back(1);
	data.push_back(std::make_pair(-0.1, -1.0)); labels.push_back(-1);
	data.push_back(std::make_pair(-1.0, 1.1)); labels.push_back(-1);
	data.push_back(std::make_pair(2.1, -3)); labels.push_back(1);

	SVM svm;

	for (auto i(0); i < 1000; i++)
	{
		auto j = (rand() % data.size());
		auto x = std::make_shared<Unit>(data[j].first, 0.0);
		auto y = std::make_shared<Unit>(data[j].second, 0.0);
		auto label = labels.at(j);
		svm.learn(x, y, label);

		if (!(i % 25)) {
			auto k = 0, correct_data(0);
			for (const auto& x : data)
			{
				auto res = svm.forward(std::make_shared<Unit>(x.first, 0.0), std::make_shared<Unit>(x.second, 0.0))->val > 0 ? 1 : -1;
				if (res == labels.at(k++))
					correct_data++;
			}
			std::cout << i << " " << correct_data / static_cast<double>(data.size()) << std::endl;
			if (correct_data / static_cast<double>(data.size()) == 1)
				break;
		}
	}
	std::cout << "     " << svm.a->val << " " << svm.b->val << " " << svm.c->val << std::endl;
	system("pause");
}





int main1()
{
	auto a = std::make_shared<Unit>(1.0, 0.0);
	auto b = std::make_shared<Unit>(2.0, 0.0);
	auto c = std::make_shared<Unit>(-3.0, 0.0);
	auto x = std::make_shared<Unit>(-1.0, 0.0);
	auto y = std::make_shared<Unit>(3.0, 0.0);

	MultiplyGate mulg1, mulg2;
	AddGate addg1, addg2;
	SigmoidGate sigg1;
NEURON_NET:
	//	auto f1 = [&]()
	//	{
	auto &ax = mulg1.forward(a, x);
	auto &by = mulg2.forward(b, y);
	auto &axpby = addg1.forward(ax, by);
	auto &axpbypc = addg2.forward(axpby, c);
	auto &s = sigg1.forward(axpbypc);
	std::cout << s->val << std::endl;

	s->grad = -1.0;
	//	};
	//	f1();

	sigg1.backward();
	addg2.backward();
	addg1.backward();
	mulg2.backward();
	mulg1.backward();

	auto step_size = 0.01;
	a->val += step_size * a->grad; // a.grad is -0.105
	b->val += step_size * b->grad; // b.grad is 0.315
	c->val += step_size * c->grad; // c.grad is 0.105
	x->val += step_size * x->grad; // x.grad is 0.105
	y->val += step_size * y->grad; // y.grad is 0.210
	goto NEURON_NET;
	//	ax = mulg1.forward(a, x);
	//	by = mulg2.forward(b, y);
	//	axpby = addg1.forward(ax, by);
	//	axpbypc = addg2.forward(axpby, c);
	//	s = sigg1.forward(axpbypc);
	//	std::cout << s->val << std::endl;

	system("pause");
	return 0;
}

*/