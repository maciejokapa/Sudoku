// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream>

using namespace std;


class Cell {
public:
	static int solved;
	int value;
	bool isChangable;
	Cell() { this->value = 0;this->isChangable = true; }
	Cell(int val) { this->value = val; (val == 0) ? (isChangable = true) : (isChangable = false); }
};

void Draw();
bool isValid(int, int, int);
void Init(int);
void Solve(int, int);
void SearchNextCell(int, int);
void SearchPreviousCell(int, int);

int Cell::solved;
Cell tab[9][9];
int cnt = 0;

int main()
{
	
	srand(time(NULL));
	Init(10);
	Draw();
	SearchNextCell(0, -1);
	Draw();

	/*
	fstream plik;
	plik.open("data.txt", ios::in | ios::out);
	if (plik.good())
	{
		for (int i = 0;i < 9;i++)
		{
			for (int j = 0;j < 9;j++)
			{
				tab[i][j] = plik.get();
			}
		}
	}
	else
	{
	cout << "Blad pliku";
	}
	Draw();*/

	/*
	int iter;
	int sum = 0;
	for (int i = 1;i < 61;i++)
	{
	for (int j = 0;j < iter;j++)
	{
	Zero(game);
	Init(game, i);
	sum += cnt;
	cnt = 0;
	}
	sum /=iter;
	cout << "liczba wpisanych pol = " << i << ". Osiagnieto srednio w " << sum << " probach."<<endl;
	sum = 0;
	}
	cout << "koniec";*/
	int n;
	cin >> n;
	return 0;
}


void Draw()
{
	cout << "-------------------------------------" << endl << "| ";
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tab[i][j].value != 0)
				cout << tab[i][j].value << " | ";
			else
				cout << "  | ";
		}
		if (i % 3 == 2 && i != 8)
			cout <<endl << "|-----------|-----------|-----------|" << endl << "| ";
		else if (i != 8)
			cout <<endl << "| -   -   - | -   -   - | -   -   - |" << endl << "| ";
	}
	cout <<endl << "-------------------------------------" << endl;
}
bool isValid(int value, int y, int x)
{
	for (int i = 0;i < 9;i++)
	{
		if (value == tab[y][i].value && i != x)
		{
			return false;
		}
	}
	for (int i = 0;i < 9;i++)
	{
		if (value == tab[i][x].value && i != y)
		{
			return false;
		}
	}
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (tab[(y / 3) * 3 + j][(x / 3) * 3 + i].value == value && ((y / 3) * 3 + j) != y && ((x / 3) * 3 + i) != x)
			{
				return false;
			}
		}
	}
	return true;
}
void Init(int amount)
{
	int x, y,possibleValue;
	for (int i = 0; i < amount; )
	{
		x = rand() % 9;
		y = rand() % 9;
		possibleValue = rand() % 9 + 1;
		if (tab[y][x].isChangable && isValid(possibleValue,y,x))
		{
			tab[y][x].value = possibleValue;
			tab[y][x].isChangable = false;
			i++;
			Cell::solved++;
		}
	}
}
void Solve(int y, int x)
{
	if (Cell::solved < 81)
	{
		cnt++;
		if (cnt > 2000) { cout << "Niemozliwe do rozwiazania";return; }

		bool isSolved = false;
		while (tab[y][x].value < 9)
		{
			tab[y][x].value++;
			if (isValid(tab[y][x].value, y, x))
			{
				isSolved = true;
				break;
			}
		}

		if (isSolved)
		{
			Cell::solved++;
			SearchNextCell(y, x); 
		}
		else
		{
			Cell::solved--;
			tab[y][x].value = 0;
			SearchPreviousCell(y, x);
		}
	}
}
void SearchNextCell(int y, int x)
{
		do
		{
			if (x == 8) { x = 0;y++; }
			else { x++; }
		} while (tab[y][x].isChangable == false);
		Solve(y, x);
}
void SearchPreviousCell(int y, int x)
{
	do {
		if (x == 0) { x = 8;y--; }
		else { x--; }
	} while (tab[y][x].isChangable == false);
	Solve(y, x);
}