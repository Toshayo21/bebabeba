#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

enum Tile
{
	UNKNOWN,
	FILLED,
	EMPTY
};

bool isRowComplete(vector<vector<Tile>> r, vector<int> hints, int row, int width)
{
	bool empty = 1;
	int currentLen = 0;
	int t = -1;
	for (int i = 0; i < width; i++)
		if (r[row][i] == FILLED)
			if (empty)
			{
				empty = 0;
				t++;
				currentLen = 1;
			}
			else
				currentLen++;
		else if (!empty)
		{
			empty = 1;
			if (!(hints[t] == currentLen))
				return false;
		}

	if (!empty && !(hints[t] == currentLen))
		return false;
	return true;
}

bool isColumnComplete(vector<vector<Tile>> r, vector<int> hints, int column, int height)
{
	bool empty = 1;
	int currentLen = 0;
	int t = -1;
	for (int i = 0; i < height; i++)
		if (r[i][column] == FILLED)
			if (empty)
			{
				empty = 0;
				t++;
				currentLen = 1;
			}
			else
				currentLen++;
		else if (!empty)
		{
			empty = 1;
			if (!(hints[t] == currentLen))
				return false;
		}

	if (!empty && !(hints[t] == currentLen))
		return false;
	return true;
}

bool isComplete(vector<vector<Tile>> r, vector<vector<int>> hintsH, vector<vector<int>> hintsV, int height, int width)
{
	for (int i = 0; i < height; i++)
		if (!isRowComplete(r, hintsH[i], i, width))
			return false;

	for (int i = 0; i < width; i++)
		if (!isColumnComplete(r, hintsV[i], i, height))
			return false;

	return true;
}

void readFile(int& height, int& width, vector<vector<int>> &hintsH, vector<vector<int>> &hintsV)
{
	string str;
	ifstream file("filenme.txt");
	if (!file)
	{
		cout << "Error reading file";
		exit(-1);
	}
	file >> height >> width;

	vector<vector<int>> H(width, vector<int>());
	vector<vector<int>> V(height, vector<int>());

	getline(file, str);
	for (int i = 0; i < height; i++)
	{
		getline(file, str);
		istringstream ss(str);
		int num;
		while (ss >> num)
			H[i].push_back(num);
	}
	for (int i = 0; i < width; i++)
	{
		getline(file, str);
		istringstream ss(str);
		int num;
		while (ss >> num)
			V[i].push_back(num);

	}

	hintsH = H;
	hintsV = V;
	
	file.close();
}

int main()
{
	int width, height;
	vector<vector<int>> hintsV;
	vector<vector<int>> hintsH;
	readFile(width, height, hintsH, hintsV);
	vector<vector<Tile>> r(width, vector<Tile>(height));
	
	r[0][2] = FILLED;
	r[0][4] = FILLED;

	r[1][3] = FILLED;
	r[1][4] = FILLED;

	r[2][3] = FILLED;
	r[2][4] = FILLED;

	r[3][0] = FILLED;
	r[3][1] = FILLED;
	r[3][3] = FILLED;
	r[3][4] = FILLED;

	r[4][0] = FILLED;
	r[4][1] = FILLED;
	r[4][2] = FILLED;


	cout << isComplete(r, hintsH, hintsV, height, width);

	return 0;
}
