#include "Parcer.h"
#include "NeuralNetwork.h"
#include "Data.h"

#include <ctime>
#include <iostream>
#include <iomanip>

void main ()
{
	srand(time(NULL));

	/// translate Training data to a usable format
	std::vector<Data::TrainingDrawing> drawingData;
	ParceData("Data/train.csv", &drawingData, 0);
	int const parcedDataSize = drawingData.size();
	int const segmentSize = parcedDataSize / 10;
	///===========================================

	/// Create the Neural Network
	int layerSizes[] = { 784, 100, 10 };
	NeuralNetwork NN(layerSizes, sizeof(layerSizes) / sizeof(int) );
	double accuracy = 0;
	double pastAccuracy = 0;
	/// =========================

	int onSegment = 0;
	int loopThrough = 3;
	int loop = 0;

	do
	{
		int TrainBegin = onSegment * segmentSize;
		int TrainEnd = (onSegment + 1) * segmentSize;

		for (int i = TrainBegin; i < TrainEnd; i++)
		{
			NN.Guess(&drawingData[i]);
			NN.Learn(drawingData[i].label);
		}

		double correct = 0;
		double mistaken = 0;

		for (int i = 0; i < parcedDataSize; i++)
		{
			if ( i < TrainBegin || TrainEnd < i)
			{
				if (NN.Guess(&drawingData[i]) == drawingData[i].label)
				{
					correct++;
				}
				else
				{
					mistaken++;
				}
			}
		}

		accuracy = correct / (correct + mistaken);
		std::cout << "accuracy: " << accuracy * 100 << "% " << "on segment: " << onSegment << std::endl;

		if (pastAccuracy /accuracy > 0.92)
		{
			onSegment++;
		}

		pastAccuracy = accuracy;

		if (onSegment >= 10)
		{
			loop++;
			onSegment = 0;
		}
	}
	while (loop < loopThrough);
	
	
	double correct = 0;
	double mistaken = 0;

	for (int i = 0; i < parcedDataSize; i++)
	{
		if (NN.Guess(&drawingData[i]) == drawingData[i].label)
		{
			correct++;
		}
		else
		{
			mistaken++;
		}
	}
	accuracy = correct / (correct + mistaken);
	std::cout << "Final Accuracy: " << accuracy * 100 << "%" << std::endl;

	/*
	//print numbers nd their labels
	int showDrawing = drawingData.size();
	for (int digit = 0; digit < showDrawing; digit++)
	{
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				std::cout << std::setw(6) << std::setprecision(3) << drawingData[digit].pixel[i][j];
			}

			std::cout << std::endl << std::endl;;
		}
		std::cout << "=====" << drawingData[digit].label << "=====";

		std::cout << std::endl << std::endl << std::endl;
	}
	
	*/
	system("pause");
}
