#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int layerSizesInp[], int layerArrLen)
{
	layerLen = layerArrLen;
	layerSizes = layerSizesInp;
	neurons = new Neuron**[layerLen];

	for (int i = 0; i < layerLen; i++)
	{
		if (i == 0)
		{
			neurons[i] = new Neuron*[layerSizes[i]];
		}
		else
		{
			neurons[i] = new Neuron*[layerSizes[i]];
		}
		
	}

	InitNeurons();
}

void NeuralNetwork::InitNeurons()
{
	for (int i = 0; i < layerLen; i++)
	{
		for (int j = 0; j < layerSizes[i]; j++)
		{
			if (i == 0)
			{
				neurons[i][j] = new Neuron();
			}
			else
			{
				neurons[i][j] = new Neuron(neurons[i - 1], layerSizes[i - 1]);
			}
		}
	}
}

int NeuralNetwork::Guess(Data::TrainingDrawing* picture)
{
	FeedForward(&picture->pixel[0][0], sizeof(picture->pixel) / sizeof(double));

	double biggestVal = 0;
	int biggestID = 0;
	double total = 0;

	for (int i = 0; i < layerSizes[layerLen - 1]; i++)
	{
		double valueInQ = neurons[layerLen - 1][i]->value;
		total += valueInQ;
		if (valueInQ > biggestVal)
		{
			biggestVal = valueInQ;
			biggestID = i;
		}
	}

	//std::cout << "total is " << total << std::endl;
	return biggestID;
}

void NeuralNetwork::FeedForward(double* input, int inputSize)
{
	
	
	if (inputSize != layerSizes[0])
	{
		std::cout << std::endl << "ERROR! -> input doesn't match the input neuron size" << std::endl;
		return;
	}

	for (int i = 0; i < layerLen; i++)
	{
		for (int j = 0; j < layerSizes[i]; j++)
		{
			if (i == 0)
			{
				neurons[0][j]->value = input[j];
			}
			else
			{
				neurons[i][j]->Calculate();
			}
		}
	}
	
}

void NeuralNetwork::Learn(int correctLabel)
{
	int const outputLen = layerSizes[layerLen - 1];
	double* wantedOutput = new double[outputLen];

	for (int i = 0; i < outputLen; i++)
	{
		if (i == correctLabel)
		{
			wantedOutput[i] = 1;
		}
		else
		{
			wantedOutput[i] = 0;
		}
		
	}

	BackPropagation(wantedOutput);
}

void NeuralNetwork::BackPropagation(double wantedOutput[])
{
	for (int i = layerLen - 1; i > 1; i--)
	{
		for (int j = 0; j < layerSizes[i]; j++)
		{
			if (i == layerLen - 1)
			{
				neurons[layerLen - 1][j]->FeedError((wantedOutput[j] - neurons[layerLen - 1][j]->value) * learningRate);
			}
			else
			{
				neurons[i][j]->CalculateError();
			}
		}
	}
}



