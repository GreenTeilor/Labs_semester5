#pragma once
#include "Cell.h" 
#include <vector>
#include <random>

class Field
{
private:
	struct Coordinates
	{
		int x, y;
	};

	static std::random_device rd;
	static std::mt19937 mersenne;

	std::vector<std::vector<Cell>> m_field;
	bool m_isDeminingStarted;
	bool m_isGameOver;
	int m_numMines;
	int m_cellsRevealed;
	int m_width;
	int m_height;

	bool outBounds(int x, int y);

public:
	Field(int width, int height, int numMines);
	bool isGameEnded();
	bool isDemined();
	int generateInt(int min, int max);
	int calcBombsNear(int x, int y);
	void countBombsNearEachCell();
	void moveAwayBomb(int x, int y);
	void reveal(int x, int y);
	void generate(int width, int height, int numMines);
	std::vector<Cell>& operator[](const int index);
	int getHeight();
	int getWidth();
};

