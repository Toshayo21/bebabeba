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

bool isColumnComplete(vector<vector<Tile>> r, vector<int> hints, int column, int height)
{
	bool empty = 1;
	int currentLen = 0;
	int t = -1;
	for (int i = 0; i < height; i++)
		if (r[column][i] == FILLED)
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

bool isRowComplete(vector<vector<Tile>> r, vector<int> hints, int row, int width)
{
	bool empty = 1;
	int currentLen = 0;
	int t = -1;
	for (int i = 0; i < width; i++)
		if (r[i][row] == FILLED)
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
	for (int i = 0; i < width; i++)
		if (!isColumnComplete(r, hintsH[i], i, height))
			return false;

	for (int i = 0; i < height; i++)
		if (!isRowComplete(r, hintsV[i], i, width))
			return false;

	return true;
}

void readFile(int& height, int& width, vector<vector<int>>& hintsH, vector<vector<int>>& hintsV)
{
	string str;
	ifstream file("filenme.txt");
	if (!file)
	{
		cout << "Error reading file";
		exit(-1);
	}
	file >> height >> width;

	vector<vector<int>> H(height, vector<int>());
	vector<vector<int>> V(width, vector<int>());

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

bool increment(vector<int>& offsets, int maxvalue)
{
	bool b = 1;
	int i = offsets.size() - 1;
	while (b)
	{
		offsets[i]++;
		b = 0;
		if (offsets[i] > maxvalue)
		{
			i--;
			b = 1;
		}
		if (i < 0)
			return false;
	}
	for (int j = i + 1; j < offsets.size(); j++)
		offsets[j] = offsets[i];

	return true;
}

void enumerateRow(vector<vector<Tile>>& r, vector<int> hints, int rowNumber)
{
	int w = r[0].size();

	int numberOfBlocks = hints.size();
	vector<bool> currentConfiguration(w);
	vector<int> offsets(numberOfBlocks);
	vector<int> maxOffsets(numberOfBlocks);
	vector<int> startpos(numberOfBlocks);

	int margin = w + 1;
	for (int i = 0; i < numberOfBlocks; i++)
		margin -= hints[i] + 1;

	startpos[0] = 0;
	for (int i = 1; i < numberOfBlocks; i++)
		startpos[i] = startpos[i - 1] + hints[i - 1] + 1;

	bool t = 1;
	int validConfigurations = 0;
	vector<int> occuredPerTile(w);
	while (t)
	{
		for (int i = 0; i < w; i++)
			currentConfiguration[i] = 0;
		for (int i = 0; i < numberOfBlocks; i++)
			for (int j = 0; j < hints[i]; j++)
				currentConfiguration[startpos[i] + offsets[i] + j] = 1;

		bool valid = 1;
		for (int i = 0; i < w; i++)
			if ((currentConfiguration[i] && (r[rowNumber][i] == EMPTY))
				|| (!currentConfiguration[i] && (r[rowNumber][i] == FILLED)))
				valid = 0;

		if (valid)
		{
			for (int i = 0; i < w; i++)
				if (currentConfiguration[i])
					occuredPerTile[i]++;
			validConfigurations++;
			//testoutput(currentConfiguration);
		}

		t = increment(offsets, margin);
	}
	for (int i = 0; i < w; i++)
		if (occuredPerTile[i] == 0)
			r[rowNumber][i] = EMPTY;
		else if (occuredPerTile[i] == validConfigurations)
			r[rowNumber][i] = FILLED;
}

void output(vector<vector<Tile>> r)
{
	int h = r.size(), w = r[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (r[i][j] == FILLED)
				cout << '0';
			else
				cout << '.';
		}
		cout << endl;
	}
}

void enumerateColumn(vector<vector<Tile>>& r, vector<int> hints, int columnNumber)
{
	int h = r.size();

	int numberOfBlocks = hints.size();
	vector<bool> currentConfiguration(h);
	vector<int> offsets(numberOfBlocks);
	vector<int> maxOffsets(numberOfBlocks);
	vector<int> startpos(numberOfBlocks);

	int margin = h + 1;
	for (int i = 0; i < numberOfBlocks; i++)
		margin -= hints[i] + 1;

	startpos[0] = 0;
	for (int i = 1; i < numberOfBlocks; i++)
		startpos[i] = startpos[i - 1] + hints[i - 1] + 1;

	bool t = 1;
	int validConfigurations = 0;
	vector<int> occuredPerTile(h);
	while (t)
	{
		for (int i = 0; i < h; i++)
			currentConfiguration[i] = 0;
		for (int i = 0; i < numberOfBlocks; i++)
			for (int j = 0; j < hints[i]; j++)
				currentConfiguration[startpos[i] + offsets[i] + j] = 1;

		bool valid = 1;
		for (int i = 0; i < h; i++)
			if ((currentConfiguration[i] && (r[i][columnNumber] == EMPTY))
				|| (!currentConfiguration[i] && (r[i][columnNumber] == FILLED)))
				valid = 0;

		if (valid)
		{
			for (int i = 0; i < h; i++)
				if (currentConfiguration[i])
					occuredPerTile[i]++;
			validConfigurations++;
			//testoutput(currentConfiguration);
		}

		t = increment(offsets, margin);
	}
	for (int i = 0; i < h; i++)
		if (occuredPerTile[i] == 0)
			r[i][columnNumber] = EMPTY;
		else if (occuredPerTile[i] == validConfigurations)
			r[i][columnNumber] = FILLED;
}


int main()
{
	int width, height;
	vector<vector<int>> hintsH;
	vector<vector<int>> hintsV;
	readFile(height, width, hintsH, hintsV);
	vector<vector<Tile>> r(height, vector<Tile>(width));

	for (int c = 0; c < 15; c++)
	{
		for (int i = 0; i < height; i++)
			enumerateRow(r, hintsH[i], i);
		for (int i = 0; i < width; i++)
			enumerateColumn(r, hintsV[i], i);
	}

	output(r);

	return 0;
}
