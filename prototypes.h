#pragma once

#include <iostream>
#include <vector>
#include <map>
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
void printVector(vector<int>&);
void printVector(matrix&);
vector<int> changeOrderNodes(matrix&, vector<int>&);
matrix findNextWorks(matrix&);
vector<int> findEarlyStart(matrix&, vector<int>&);
vector<int> findEarlyEnd(matrix&, vector<int>&);
vector<int> findCriticalPathLength(vector<int>&, vector<int>&, vector<int>&);
vector<int> findTimeReserve(vector<int>&, int);
vector<int> readVector(string, int);
