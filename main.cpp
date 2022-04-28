#include <iostream>
#include <vector>
#define SIZE 10
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
	{
		if (r[row][i] == FILLED)
		{
			if (empty)
			{
				empty = 0;
				t++;
				currentLen = 1;
			}
			else
			{
				currentLen++;
			}
		}
		else
		{
			if (!empty)
			{
				//cout << currentLen << endl;
				empty = 1;
				if (!(hints[t] == currentLen))
				{
					return false;
				}
			}
		}
	}

	if (!empty)
	{
		//cout << currentLen << endl;;
		if (!(hints[t] == currentLen))
		{
			return false;
		}
	}
	return true;
}

bool isColumnComplete(vector<vector<Tile>> r, vector<int> hints, int column, int height)
{
	bool empty = 1;
	int currentLen = 0;
	int t = -1;
	for (int i = 0; i < height; i++)
	{
		if (r[i][column] == FILLED)
		{
			if (empty)
			{
				empty = 0;
				t++;
				currentLen = 1;
			}
			else
			{
				currentLen++;
			}
		}
		else
		{
			if (!empty)
			{
				//cout << currentLen << endl;
				empty = 1;
				if (!(hints[t] == currentLen))
				{
					return false;
				}
			}
		}
	}

	if (!empty)
	{
		//cout << currentLen << endl;;
		if (!(hints[t] == currentLen))
		{
			return false;
		}
	}
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

int main()
{
	int width, height;
	vector<vector<Tile>> r(5, vector<Tile>(5));
	vector<vector<int>> hintsH(5, vector<int>(SIZE));
	vector<vector<int>> hintsV(5, vector<int>(SIZE));

	width = 5, height = 5;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			r[i][j] = UNKNOWN;
		}
	}

	//sample array
	//----------------------
	r[0][2] = FILLED;
	r[0][3] = FILLED;
	r[0][4] = FILLED;

	r[1][0] = FILLED;
	r[1][2] = FILLED;
	r[1][4] = FILLED;

	r[2][0] = FILLED;
	r[2][1] = FILLED;
	r[2][4] = FILLED;

	r[3][0] = FILLED;
	r[3][1] = FILLED;

	r[4][0] = FILLED;
	r[4][4] = FILLED;


	hintsH[0][0] = 3;

	hintsH[1][0] = 1;
	hintsH[1][1] = 1;
	hintsH[1][2] = 1;

	hintsH[2][0] = 2;
	hintsH[2][1] = 1;

	hintsH[3][0] = 2;

	hintsH[4][0] = 1;
	hintsH[4][1] = 1;


	hintsV[0][0] = 4;

	hintsV[1][0] = 2;

	hintsV[2][0] = 2;

	hintsV[3][0] = 1;

	hintsV[4][0] = 3;
	hintsV[4][1] = 1;
	//----------------------

	cout << isComplete(r, hintsH, hintsV, height, width);

	return 0;
}
