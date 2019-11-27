#pragma once
#include <cmath>

class Neuron
{
private:
	Neuron** inputNeurons;
	int weightsLen;
	double* weights;
	double bias;
	double Sigmoid(double inp);
	double error;
	void EditWeights();

public:
	double value = 0;
	Neuron(Neuron** inpNrns, int inpNeuronSize);
	Neuron();
	void Calculate();
	void FeedError(double errorInp);
	void CalculateError();
	void AddToError(double errorInp);
};

