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

void ReadFile(int& height, int& width, vector<vector<int>>& hintsH, vector<vector<int>>& hintsV)
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

bool Increment(vector<int>& offsets, int maxvalue)
{
	bool b = 1;
	int i = (int)offsets.size() - 1;
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

void Output(vector<vector<Tile>> r, bool showBorders = 1, bool showEmpty = 0)
{
	int h = (int)r.size(), w = (int)r[0].size();
	for (int i = 0; i < h; i++)
	{
		cout << endl;
		if (showBorders)
			if (i % 5 == 0 && i != 0)
			{
				for (int i = 0; i < w + w / 5; i++)
					cout << '-';
				cout << endl;
			}
		for (int j = 0; j < w; j++)
		{
			if (showBorders)
				if (j % 5 == 0 && j != 0)
					cout << '|';
			if (r[i][j] == FILLED)
				cout << '0';
			else if (showEmpty && r[i][j] == EMPTY)
				cout << 'x';
			else
				cout << '.';
		}

	}
	cout << endl;
}

int EnumerateColumn(vector<vector<Tile>>& r, vector<int> hints, int columnNumber)
{
	int h = (int)r.size();

	int numberOfBlocks = (int)hints.size();
	vector<bool> currentConfiguration(h);
	vector<int> offsets(numberOfBlocks);
	vector<int> maxOffsets(numberOfBlocks);
	vector<int> startPos(numberOfBlocks);

	int margin = h + 1;
	for (int i = 0; i < numberOfBlocks; i++)
		margin -= hints[i] + 1;

	startPos[0] = 0;
	for (int i = 1; i < numberOfBlocks; i++)
		startPos[i] = startPos[i - 1] + hints[i - 1] + 1;

	bool t = 1;
	int validConfigurations = 0;
	vector<int> occuredPerTile(h);
	while (t)
	{
		for (int i = 0; i < h; i++)
			currentConfiguration[i] = 0;
		for (int i = 0; i < numberOfBlocks; i++)
			for (int j = 0; j < hints[i]; j++)
				currentConfiguration[startPos[i] + offsets[i] + j] = 1;

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

		t = Increment(offsets, margin);
	}
	int dif = 0;
	for (int i = 0; i < h; i++)
		if (r[i][columnNumber] == UNKNOWN)
		{
			if (occuredPerTile[i] == 0)
			{
				dif++;
				r[i][columnNumber] = EMPTY;
			}
			else if (occuredPerTile[i] == validConfigurations)
			{
				dif++;
				r[i][columnNumber] = FILLED;
			}
		}
	return dif;
}

int EnumerateRow(vector<vector<Tile>>& r, vector<int> hints, int rowNumber)
{
	int w = (int)r[0].size();

	int numberOfBlocks = (int)hints.size();
	vector<bool> currentConfiguration(w);
	vector<int> offsets(numberOfBlocks);
	vector<int> maxOffsets(numberOfBlocks);
	vector<int> startPos(numberOfBlocks);

	int margin = w + 1;
	for (int i = 0; i < numberOfBlocks; i++)
		margin -= hints[i] + 1;

	startPos[0] = 0;
	for (int i = 1; i < numberOfBlocks; i++)
		startPos[i] = startPos[i - 1] + hints[i - 1] + 1;

	bool t = 1;
	int validConfigurations = 0;
	vector<int> occuredPerTile(w);
	while (t)
	{
		for (int i = 0; i < w; i++)
			currentConfiguration[i] = 0;
		for (int i = 0; i < numberOfBlocks; i++)
			for (int j = 0; j < hints[i]; j++)
				currentConfiguration[startPos[i] + offsets[i] + j] = 1;

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

		t = Increment(offsets, margin);
	}
	int dif = 0;
	for (int i = 0; i < w; i++)
		if (r[rowNumber][i] == UNKNOWN)
		{
			if (occuredPerTile[i] == 0)
			{
				dif++;
				r[rowNumber][i] = EMPTY;
			}
			else if (occuredPerTile[i] == validConfigurations)
			{
				dif++;
				r[rowNumber][i] = FILLED;
			}
		}

	return dif;
}

void enumeration(vector<vector<Tile>> &r, vector<vector<int>> hintsH, vector<vector<int>> hintsV)
{
	int width = (int)r[0].size();
	int height = (int)r.size();
	int remaining = width * height;
	while (remaining > 0)
	{
		for (int i = 0; i < height; i++)
			remaining -= EnumerateRow(r, hintsH[i], i);
		for (int i = 0; i < width; i++)
			remaining -= EnumerateColumn(r, hintsV[i], i);
	}
}

int main()
{
	int width, height;
	vector<vector<int>> hintsH;
	vector<vector<int>> hintsV;
	ReadFile(height, width, hintsH, hintsV);
	vector<vector<Tile>> r(height, vector<Tile>(width));

	cout << endl;
	enumeration(r, hintsH, hintsV);
	Output(r, 0, 0);
	return 0;
}
