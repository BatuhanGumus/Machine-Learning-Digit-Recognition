#include "Neuron.h"

Neuron::Neuron(Neuron** inpNrns, int inpNeuronSize)
{
	inputNeurons = inpNrns;
	weightsLen = inpNeuronSize;
	weights = new double[weightsLen];
	for (int i = 0; i < weightsLen; i++)
	{
		weights[i] = (((rand() * 1.0) / RAND_MAX) * 2) - 1;
	}
	bias = (((rand() * 1.0) / RAND_MAX) * 2) - 1;
}

Neuron::Neuron()
{
	
}

void Neuron::Calculate()
{
	value = 0;

	for (int i = 0; i < weightsLen; i++)
	{
		value += inputNeurons[i]->value * weights[i];
	}
	value += bias;
	value = Sigmoid(value);
}

double Neuron::Sigmoid(double inp)
{
	return 1 / (1 + exp(-inp));
}

void Neuron::FeedError(double errorInp)
{
	error = errorInp;
	CalculateError();
}

void Neuron::CalculateError()
{
	double totalWeights = 0;

	for (int i = 0; i < weightsLen; i++)
	{
		totalWeights += weights[i];
	}
	totalWeights += bias;

	for (int i = 0; i < weightsLen; i++)
	{
		double passError = error * (weights[i] / totalWeights);
		inputNeurons[i]->AddToError(passError);
	}

	EditWeights();

	error = 0;
}

void Neuron::EditWeights()
{
	double const errorStable = error * (value * (1 - value));

	for (int  i = 0; i < weightsLen; i++)
	{
		weights[i] += inputNeurons[i]->value * errorStable;
	}
	bias += error * errorStable;
}


void Neuron::AddToError(double errorInp)
{
	error += errorInp;
}

