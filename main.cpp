#include <iostream>
#include <vector>
#define lenght 25
using namespace std;

enum Tile
{
	UNKNOWN,
	FILLED,
	EMPTY
};

void emptytiles(vector<vector<Tile>> r) { // Заповнення двовимірного вектора порожніми клітинами
	for (int i = 0; i < lenght, i++) // lenght - ширина і висота вектора
		for (int j = 0; j < lenght; j++)
			if (r[i][j] == UNKNOWN) // перевірка чи є елемент порожнім 
				r[i][j] = EMPTY; // заповнення порожніми клітинами 
} 

void ifdone(vector<vector<Tile>> r, vector<vector<Tile>> k) { // перевірка на правильність опрацювання вектора
	// k - вектор, який складається з векторів, що містять довжини заповнених клітинок
	int n = 0, t = 0; // створюємо лічильники
	for (int i = 0; i < lenght, i++) // lenght - ширина і висота вектора
		for (int j = 0; j < lenght; j++) {  
			if (r[i][j] == FILLED) // перевірка на правильність заповнення 
				n++;	
			else if (n == k[t]) 
				t++; // рухаємося по t			}
			else {
				perror("Error: Incorrect meaning"); // вивід помилки і вихід з програми
				exit(-1);
			}   
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
