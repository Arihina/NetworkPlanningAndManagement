#include "prototypes.h"

void main() 
{
	int defaultSize = 9; // default size of vector from file
	string defaultVector = "exampleVector.txt", defaultMatrix = "exampleMatrix.txt";

	cout << "Use default input files? y/n " << endl;
	char answer;
	cin >> answer;

	if (answer != 'y')
	{
		if (answer != 'n')
		{
			cout << "Invalid character. The default settings are set." << endl;
		}
		else
		{
			cout << "Enter a size of input vector: ";
			cin >> defaultSize;

			cout << "Enter file name for input matrix: ";
			cin >> defaultMatrix;

			cout << "Enter file name for input vector: ";
			cin >> defaultVector;
		}
	}
	cout << endl;

	vector<int> weights = readVector(defaultVector, defaultSize);
	matrix times;
	matrix matrix = readMatrix(defaultMatrix, defaultSize);

	if (findCycle(matrix)) 
	{
		cout << "The original matrix contains a cycle" << endl;
		cout << "The task cannot be solved for a matrix with a cycle" << endl;
		return;
	}

	vector<int> sourceNodes = findSource(matrix);
	vector<int> drainNodes = findDrain(matrix);

	extendMatrix(matrix, sourceNodes, drainNodes);

	vector<int> order = changeOrderNodes(matrix, weights);
	cout << "Order of execution of works " << endl;
	printVector(order);

	cout << "Duration of work" << endl;
	printVector(weights);
	
	times = findNextWorks(matrix);
	cout << "Related nodes" << endl;
	printVector(times);

	vector<int> startWorks = findEarlyStart(matrix, weights);
	cout << "Early start of works " << endl;
	printVector(startWorks);

	vector<int> endWorks = findEarlyEnd(matrix, weights);
	cout << "Early start of works " << endl;
	printVector(endWorks);

	vector<int> criticalPaths = findCriticalPathLength(weights, startWorks, endWorks);
	cout << "Critical Path Length" << endl;
	printVector(criticalPaths);

	int maxLen = *max_element(criticalPaths.begin(), criticalPaths.end());

	vector<int> reserve = findTimeReserve(criticalPaths, maxLen);
	cout << "Time reserve " << endl;
	printVector(reserve);

	cout << "Max length of the critical path = " << maxLen << endl;
	cin >> answer;
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

vector<int> fillRandomVector(int size)
{
	vector<int> result;

	for (int i = 0; i < size; i++)
	{
		result.push_back(rand() % 10);
	}

	return result;
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

void printVector(vector<int>& vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

void printVector(matrix& matrix) 
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << " ";
	}
	cout << endl;
}

// Function for read matrix from .txt file
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

// Function for read vector from .txt file
vector<int> readVector(string fileName, int size)
{
	if (fileName.substr(fileName.find_last_of(".") + 1) != "txt")
	{
		cout << "Error. You cannot open a file with a non-txt extension";
		exit(1);
	}
	
	ifstream fin(fileName);
	vector<int> vector;
	int num;

	for (int i = 0; i < size; i++)
	{
		fin >> num;
		vector.push_back(num);
	}

	return vector;
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

vector<int> changeOrderNodes(matrix& matrix, vector<int>& weights)
{
	vector<int> visited(matrix.size(), 0);
	vector<int> resultOrder;
	topologicalSorting(matrix, 0, visited, resultOrder);
	
	reverse(resultOrder.begin(), resultOrder.end());

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

	return resultOrder;
}

// Function for finding next work from node
matrix findNextWorks(matrix& args) 
{
	matrix result;

	for (int i = 0; i < args.size(); i++)
	{
		vector<int> row;
		for (int j = 0; j < args[i].size(); j++)
		{
			if (args[i][j] > 0) 
			{
				row.push_back(j);
			}
		}
		result.push_back(row);
	}

	return result;
}

// Function for finding early start of works
vector<int> findEarlyStart(matrix& matrix, vector<int>& weights) 
{
	vector<int> startWorks(weights.size(), 0);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[j][i] == 1)
			{
				startWorks[i] = max(startWorks[i], startWorks[j] + weights[j]);
			}
		}
	}

	return startWorks;
}

// Function for finding early end of works
vector<int> findEarlyEnd(matrix& matrix, vector<int>& weights)
{
	vector<int> endWorks(weights.size(), 0);

	for (int i = matrix.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				endWorks[i] = max(endWorks[i], endWorks[j] + weights[j]);
			}
		}
	}

	return endWorks;
}

// Function for finding the length of the critical path
vector<int> findCriticalPathLength(vector<int>& weights, vector<int>& startWorks, vector<int>& endWorks)
{
	vector<int> result;
	for (int i = 0; i < weights.size(); i++)
	{
		result.push_back(weights[i] + startWorks[i] + endWorks[i]);
	}

	return result;
}

// Function for finding the time reserve
vector<int> findTimeReserve(vector<int>& criticalPaths, int maxPath)
{
	vector<int> result;

	for (int i = 0; i < criticalPaths.size(); i++)
	{
		result.push_back(maxPath - criticalPaths[i]);
	}

	return result;
}