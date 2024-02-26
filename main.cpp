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
void extendMatrix(matrix&, vector<int>&, vector<int>&);


void main() 
{
	vector<int> testWeights = { 7, 6, 9, 3, 4, 8, 5, 2, 5 };
	matrix matrix = readMatrix("test.txt", testWeights.size());
	printMatrix(matrix);

	vector<int> sourceNodes = findSource(matrix);
	vector<int> drainNodes = findDrain(matrix);

	extendMatrix(matrix, sourceNodes, drainNodes);
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

// Function for searching for source nodes
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
}

// Function for searching for drain nodes
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

	return nodes;
}

// Function for extendig matrix
void extendMatrix(matrix& matrix, vector<int>& rows, vector<int>& columns)
{
	if (!rows.empty())
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
		matrix.insert(matrix.begin(), row);

		for (int i = 0; i < rows.size(); i++)
		{
			matrix[0][rows[i] + 1] = 1;
		}
	}
	
	if (!columns.empty())
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].push_back(0);
		}

		vector<int> row;
		for (int i = 0; i < matrix.size() + 1; i++)
		{
			row.push_back(0);
		}
		matrix.push_back(row);

		for (int i = 0; i < columns.size(); i++)
		{
			matrix[columns[i] + 1][matrix[0].size() - 1] = 1;
		}
	}
}
