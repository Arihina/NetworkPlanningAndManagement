#include <iostream>
#include <vector>
#include <algorithm>
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
bool dfs(matrix&, vector<int>, int);
bool findCycle(matrix&);
void topologicalSorting(matrix&, int, vector<int>&, vector<int>&);
void changeOrderNodes(matrix&, vector<int>&);


void main() 
{
	vector<int> testWeights = { 7, 6, 9, 3, 4, 8, 5, 2, 5 };
	matrix matrix = readMatrix("test.txt", testWeights.size());
	printMatrix(matrix);

	if (findCycle(matrix)) 
	{
		cout << "The original matrix contains a cycle" << endl;
		cout << "The task cannot be solved for a matrix with a cycle" << endl;
		return;
	}

	vector<int> sourceNodes = findSource(matrix);
	vector<int> drainNodes = findDrain(matrix);

	extendMatrix(matrix, sourceNodes, drainNodes);
	cout << endl;
	printMatrix(matrix);
	

	changeOrderNodes(matrix, testWeights);
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

// Functions for finding cycles in matrixs
bool dfs(matrix& matrix, vector<int> visited, int index) 
{
	for (int i = 0; i < matrix.size(); i++)
	{
		if (matrix[index][i] == 1 && visited[i] != 2)
		{
			if (visited[i] == 1)
			{
				return true;
			}

			visited[i] = 1;
			if (dfs(matrix, visited, i))
			{
				return true;
			}
			visited[i] = 2;
		}
	}

	return false;
}

bool findCycle(matrix& matrix) 
{
	vector<int> visited;
	for (int i = 0; i < matrix.size(); i++)
	{
		visited.push_back(0);
	}

	return dfs(matrix, visited, 0);
}

// Functions for sorting nodes
void topologicalSorting(matrix& matrix, int node, vector<int>& visited, vector<int>& resultOrder)
{
	visited[node] = 1;
	for (int i = 0; i < visited.size(); i++)
	{
		if (matrix[node][i] == 1 && visited[i] == 0)
		{
			topologicalSorting(matrix, i, visited, resultOrder);
		}
	}
	resultOrder.push_back(node);
}

void changeOrderNodes(matrix& matrix, vector<int>& weights)
{
	vector<int> visited(matrix.size(), 0);
	vector<int> resultOrder;
	topologicalSorting(matrix, 0, visited, resultOrder);
	
	reverse(resultOrder.begin(), resultOrder.end());

	/*
	cout << "New order ";
	for (int i = 0; i < resultOrder.size(); i++)
	{
		cout << i << " ";
	}
	*/

	weights.insert(weights.begin(), 0);
	weights.push_back(0);

	vector<vector<int>> copyMatrix(matrix.size(), vector<int>(matrix[0].size(), 0));
	vector<int> copyWeights(weights.size(), 0);

	for (int i = 0; i < resultOrder.size(); i++)
	{
		int rowIndex = resultOrder[i];
		copyWeights[i] = weights[resultOrder[i]];
		for (int j = 0; j < resultOrder.size(); j++)
		{
			int columnIndex = resultOrder[j];
			copyMatrix[i][j] = matrix[rowIndex][columnIndex];
		}
	}

	matrix = copyMatrix;
	weights = copyWeights;
}