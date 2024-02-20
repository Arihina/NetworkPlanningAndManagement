#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

matrix fillRandomMatrix(int);
void printMatrix(matrix&);
matrix readMatrix(string, int);


void main() 
{
	matrix matrix = fillRandomMatrix(16);
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