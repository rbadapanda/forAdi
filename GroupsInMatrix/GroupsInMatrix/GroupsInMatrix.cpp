// GroupsInMatrix.cpp : Groups in the given nXm matrix.
// Assumptions:
//	Matrix contains all the values for a nXm matrix
//	Each line contains same number of columns as the first row
//	No line is bigger than 256chars (for getline)
//	whole matrix fits in memory
//	I CAN destroy the matrix

//Features:
//	Space requirement O(N) - Visited Matrix
//	Run-time requirement O(N)



#include "stdafx.h"
using namespace std;

void readMatrix(vector<vector<int>> & v, string fname) {
	string line;
    ifstream myFile(fname);

	while (myFile)
	{
		int i;
		do getline(myFile, line); while (line.find_first_of("//", 0) != string::npos); //skip the comments
		if (line.size()) { //non-empty line read... Add it to our matrix
			v.resize(v.size() + 1);
			stringstream ss(line);
			istream_iterator<int> ii = ss;
			copy(ii, istream_iterator<int>(), back_inserter(v[v.size() - 1]));
		}
	}
}

void printMatrix(vector<vector<int>> &v) {
	for (size_t i = 0; i < v.size(); i++)
	{
		for (size_t j = 0; j < v[0].size(); j++)
		{
			cout << v[i][j] << '\t';
		}
		cout << endl;
	}
}

void countGrps(vector<vector<int>> & mat, int R, int C, int r = 0, int c = 0) {

	if (!R && !C || (r == R) || (c == C) || r < 0 || c < 0 || !mat[r][c]) return ;

    mat[r][c] = 0;

    countGrps(mat, R, C, r - 1, c);
    countGrps(mat, R, C, r + 1, c);
    countGrps(mat, R, C, r, c - 1);
    countGrps(mat, R, C, r, c + 1);

}

int _tmain(int argc, _TCHAR* argv[])
{
	auto mat1 = vector<vector<int>>{
		{1,  1,  0,  0,  1 },
		{1,  0,  0,  1,  0 },
		{1,  1,  0,  1,  0 }
	};
	vector<vector<int>> mat;
	readMatrix(mat, "c:\\temp\\myMatrix.txt");
	//tracking vector
	int R = mat.size();
	int C = 0;
	if (!R) { mat = mat1; R = mat.size(); } // just a game: if we could not read anything, take our dummy one
	C = mat[0].size();
	printMatrix(mat);

	int numGrps = { 0 };

	for (size_t i = 0; i < R; i++)
	{
		for (size_t j = 0; j < C; j++)
		{
            if(!mat[i][j]) continue;

            numGrps++;
			countGrps(mat, R, C, i, j);
		}
	}

	cout << "Total no of Groups: " << numGrps << endl;
	return 0;
}