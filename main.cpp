#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

matrix fillRandomMatrix(int);
void printMatrix(matrix&);
matrix readMatrix(string, int);
vector<int> findSource(matrix&);
vector<int> findDrain(matrix&);
void extendMatrix(matrix&);


void main() 
{
	vector<int> testWeights = { 7, 6, 9, 3, 4, 8, 5, 2, 5 };
	matrix matrix = readMatrix("test.txt", testWeights.size());
	printMatrix(matrix);
	cout << endl;
	vector<int> sourceNodes = findSource(matrix);
	cout << endl;
	vector<int> drainNodes = findDrain(matrix);
	cout << endl;
	printMatrix(matrix);
}


matrix fillRandomMatrix(int size) {
	matrix matrix(size, vector<int>(size, 0));

	for (int i = 0; i < size; i++)
	{
		vector<int> row(size, 0);
		for (int j = 0; j < size; j++)
		{
			row[j] = rand() % 2;
		}
		matrix[i] = row;;
	}

	return matrix;
}

void printMatrix(matrix& matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Function for read matrix from txt file
matrix readMatrix(string fileName, int size) {
	if (fileName.substr(fileName.find_last_of(".") + 1) != "txt")
	{
		cout << "Error. You cannot open a file with a non-txt extension";
		exit(1);
	}
	ifstream fin(fileName);
	matrix matrix;
	int num;
	
	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int i = 0; i < size; i++)
		{
			fin >> num;
			row.push_back(num);
		}
		matrix.push_back(row);
	}

	fin.close();

	return matrix;
}

// Function for searching for source nodes and and adding a common node
vector<int> findSource(matrix& matrix) 
{
	int sourceCount = 0;
	vector<int> nodes;

	for (int j = 0; j < matrix.size(); j++)
	{
		bool flag = false;
		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[i][j] != 0)
			{
				flag = true;
			}
		}
		if (!flag)
		{
			sourceCount++;
			nodes.push_back(j);
		}
	}

	return nodes;
	/*
	if (sourceCount > 1)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].insert(matrix[i].begin(), 0);
		}

		vector<int> row;
		for (int i = 0; i < matrix.size() + 1; i++)
		{
			row.push_back(0);
		}
		matrix.push_back(row);

		for (int i = 0; i < nodes.size(); i++)
		{
			matrix[i + 1][0] = 1;
		}
	}
	*/
}

// Function for searching for drain nodes and and adding a common node
vector<int> findDrain(matrix& matrix) {
	int drainCount = 0;
	vector<int> nodes;

	for (int i = 0; i < matrix.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != 0)
			{
				flag = true;
			}
		}
		if (!flag)
		{
			drainCount++;
			nodes.push_back(i);
		}
	}

	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i] << " ";
	}

	return nodes;
}
