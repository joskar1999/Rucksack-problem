#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

class Rucksack
{
public:
	Rucksack()
	{

	}

	virtual ~Rucksack()
	{

	}

	void bruteForce()
	{
		int bestScore = 0, tmpScore, tmpVolume;
		int numberOfBinaryPermutations = pow(2, this->numberOfElements);
		std::vector<int> bestPermutation(this->numberOfElements, 0);

		for (int i = 0; i < numberOfBinaryPermutations; i++)
		{
			tmpScore = 0;
			tmpVolume = 0;
			decToBin(i);
			for (int j = 0; j < this->numberOfElements; j++)
			{
				tmpScore += binary[j] * itemsData[0][j];
				tmpVolume += binary[j] * itemsData[1][j];
			}
			if (tmpScore > bestScore && tmpVolume <= this->capacity)
			{
				bestScore = tmpScore;
				for (int j = 0; j < this->numberOfElements; j++)
				{
					bestPermutation[j] = binary[j];
				}
			}
		}

		for (int i = 0; i < this->numberOfElements; i++)
		{
			if (bestPermutation[i] == 1)
			{
				resultSet.push_back(i + 1);
			}
		}
	}

	void solveDynamic()
	{
		int col = this->capacity, row = this->numberOfElements;

		for (int i = 1; i <= this->numberOfElements; i++)
		{
			for (int j = 1; j <= this->capacity; j++)
			{
				if (j < itemsData[1][i - 1])
				{
					rucksackTable[i][j] = rucksackTable[i - 1][j];
				}
				else
				{
					rucksackTable[i][j] = max(rucksackTable[i - 1][j], rucksackTable[i - 1][j - itemsData[1][i - 1]] + itemsData[0][i - 1]);
				}
			}
		}

		while (col > 0 && row > 0)
		{
			if (rucksackTable[row][col] > rucksackTable[row - 1][col])
			{
				resultSet.push_back(row--);
				col -= itemsData[1][row];
			}
			else
			{
				row--;
			}
		}
	}

	void generateRucksackData(int capacity, int numberOfElements)
	{
		int volume, value;
		std::string fileName = "rucksackData" + std::to_string(capacity) + "-" + std::to_string(numberOfElements) + ".txt";
		file.open(fileName, std::fstream::out);
		file << capacity << std::endl << numberOfElements << std::endl;
		for (int i = 0; i < numberOfElements; i++)
		{
			volume = rand() % 15 + 1;
			value = rand() % 30 + 1;
			file << value << " " << volume << std::endl;
		}
		file.close();
	}

	void printItemsTable()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < this->numberOfElements; j++)
			{
				std::cout << itemsData[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

	void printRucksackTable()
	{
		for (int i = 0; i <= this->numberOfElements; i++)
		{
			for (int j = 0; j <= this->capacity; j++)
			{
				std::cout << rucksackTable[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

	void printResultSet()
	{
		for each (int i in resultSet)
		{
			std::cout << i << "\t";
		}
	}

	void initRucksack(int capacity, int numberOfElements)
	{
		this->capacity = capacity;
		this->numberOfElements = numberOfElements;
		std::string fileName = "rucksackData" + std::to_string(capacity) + "-" + std::to_string(numberOfElements) + ".txt";
		readDataFromFile(fileName);
	}

	void clearResultSet()
	{
		resultSet.clear();
	}

	void clearRucksack()
	{
		rucksackTable.clear();
		itemsData[0].clear();
		itemsData[1].clear();
		clearResultSet();
	}



private:
	std::fstream file;
	std::vector<std::vector<int>> itemsData;
	std::vector<int> resultSet;
	std::vector<std::vector<int>> rucksackTable;
	std::vector<int> binary;
	int numberOfElements;
	int capacity;

	void readDataFromFile(std::string fileName)
	{
		std::string data;
		std::string val, vol;
		int value, volume;

		file.open(fileName, std::fstream::in);
		if (!file.good())
		{
			throw;
		}

		getline(file, data);
		this->capacity = atoi(data.c_str());
		getline(file, data);
		this->numberOfElements = atoi(data.c_str());

		initTables();

		for (int i = 0; i < this->numberOfElements; i++)
		{
			file >> val >> vol;
			value = atoi(val.c_str());
			volume = atoi(vol.c_str());
			itemsData[0][i] = value;
			itemsData[1][i] = volume;
		}

		file.close();
	}

	void initTables()
	{
		std::vector<int> temp(this->numberOfElements + 1, 0);
		std::vector<int> temp2(this->capacity + 1, 0);
		this->binary = temp;
		itemsData.push_back({});
		itemsData.push_back({});

		for (int i = 0; i < this->numberOfElements; i++)
		{
			itemsData[0].push_back(0);
			itemsData[1].push_back(0);
		}
		for (int i = 0; i <= this->numberOfElements; i++)
		{
			rucksackTable.push_back(temp2);
		}
	}

	void decToBin(int decimal)
	{
		for (int i = this->numberOfElements - 1; i >= 0; i--)
		{
			binary[i] = decimal % 2;
			decimal /= 2;
		}
	}

	int max(int a, int b)
	{
		if (a >= b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
};

