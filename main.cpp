#include <iostream>
#include <vector>
using namespace std;

enum Tile
{
	UNKNOWN,
	FILLED,
	EMPTY
};

void emptytiles(vector<vector<Tile>> r) { // Заповнення двовимірного вектора порожніми клітинами
	for (int i = 0; i < row, i++) // row - ширина вектора
		for (int j = 0; j < col; j++) // col - висота вектора
			if (r[i][j] == UNKNOWN) // перевірка чи є елемент порожнім 
				r[i][j] = EMPTY; // заповнення порожніми клітинами 
} 

void ifdone(vector<vector<Tile>> r, vector<vector<Tile>> k) { // перевірка на правильність опрацювання вектора
	// k - двомірний вектор, який створений до початку роботи і який на 100% правильний
	for (int i = 0; i < row, i++) // row - ширина вектора
		for (int j = 0; j < col; j++) // col - висота вектора
			if (r[i][j] != k[i][j]) { // перевірка на правильність заповнення 
				perror("Error: Incorrect meaning"); // вивід помилки і вихід з програми в разі незбіжності з k
				exit(-1);
			}
	cout << "Congratulations! All is correct" << endl; // повідомлення про правильне виконання
}

int main()
{
	int width, height;
	vector<vector<Tile>> r;
	vector<vector<int>> hintsH;
	vector<vector<int>> hintsV;

	return 0;
}
