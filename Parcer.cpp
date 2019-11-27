#include "Parcer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>    

/// Translates a line in the train.csv file to an array data in the program
/// harddrive -> ram
/// can translate the given amount
///  parceAmount = 0 to translate all available data
void ParceData(std::string dataLocation, std::vector<Data::TrainingDrawing>* drawingData, int parceAmount)
{
	std::cout << "Translating: " << dataLocation << std::endl;
	auto start = std::chrono::system_clock::now();

	std::ifstream trainData; // FILE
	std::string line; // line in the file
	
	// get training data and check if its null
	trainData.open(dataLocation);
	if (trainData.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "file NOT found" << std::endl;
		return;
	}
	// =====================================

	std::getline(trainData, line); // throw away the first line that doesn't include any useful info

	int count = 0; // the amount of times the loop has executed (the amount of data we have translated)
	while (std::getline(trainData, line) && (parceAmount == 0 || count < parceAmount) )
	{
		Data::TrainingDrawing newDrawingData;
		newDrawingData.label = line[0] - '0'; // get the label of the drawing which is the first column

		int num = 0; // the pixel grayscale value [0, 255]
		for (int i = 2, j = 0, k = 0; i <= line.length(); i++)
		{
			if (line[i] == ',' || line[i] == '\0')
			{
				newDrawingData.pixel[j][k] = num / 255.0; // normalize to grayscale value
				k++;
				if (k == 28)
				{
					j++;
					k = 0;
				}
				num = 0;
			}
			else
			{
				num = (num * 10) + (line[i] - '0');
			}
		}
		
		drawingData->push_back(newDrawingData);

		count++;
	}
	trainData.close();

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Translated " << count << " pictures! elapsed time: " << elapsed_seconds.count() << std::endl;
}
