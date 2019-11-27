#pragma once
#include "Data.h"
#include "Neuron.h"
#include <iostream>

class NeuralNetwork
{
private:
	int layerLen;
	int* layerSizes;
	Neuron*** neurons;
	double learningRate = 0.1;

	void InitNeurons();
	void FeedForward(double* input, int inputSize);
	void BackPropagation(double wantedOutput[]);

public:
	NeuralNetwork(int layerSizesInp[], int layerArrSize);

	int Guess(Data::TrainingDrawing* picture);
	void Learn(int correctLabel);
};

