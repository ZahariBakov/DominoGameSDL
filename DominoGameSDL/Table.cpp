#include "Table.h"

#include <iostream>
#include <sstream>

const int matrixX = 300;
const int matrixY = 10;
const int matrixPieceSize = 32;

Table::Table() {
	this->createMap();
}

void Table::addTile(Tile& newTile, int xPos, int yPos) {
	if (firstTurn) {
		firstTurn = false;
		this->firstFree = newTile.getFirst();
		this->secondFree = newTile.getSecond();
		tableBox[yPos][xPos].setValue(newTile.getFirst());
		tableBox[yPos][xPos + 1].setValue(newTile.getSecond());
	}
	else 
	{
		if ((newTile.getSecond() == firstFree) &&
			((tableBox[yPos][xPos + 1].getValue() == firstFree) || (tableBox[yPos][xPos - 1].getValue() == firstFree) ||
				(tableBox[yPos + 1][xPos].getValue() == firstFree) || (tableBox[yPos - 1][xPos].getValue() == firstFree)) &&
			(tableBox[yPos][xPos - 1].getValue() == "*"))
		{
			std::cout << "Second tile " << newTile.getSecond() <<  " = first free " << firstFree << std::endl;
			firstFree = newTile.getFirst();
			tableBox[yPos][xPos].setValue(newTile.getSecond());
			tableBox[yPos][xPos - 1].setValue(newTile.getFirst());
		}
		else  if ((newTile.getFirst() == secondFree) &&
			((tableBox[yPos][xPos + 1].getValue() == secondFree) || (tableBox[yPos][xPos - 1].getValue() == secondFree) ||
				(tableBox[yPos + 1][xPos].getValue() == secondFree) || (tableBox[yPos - 1][xPos].getValue() == secondFree)) &&
			(tableBox[yPos][xPos + 1].getValue() == "*"))
		{
			std::cout << "First tile " << newTile.getFirst() << " = second free " << secondFree << std::endl;
			secondFree = newTile.getSecond();
			tableBox[yPos][xPos].setValue(newTile.getFirst());
			tableBox[yPos][xPos + 1].setValue(newTile.getSecond());
		}
		else if ((newTile.getSecond() == secondFree) &&
			((tableBox[yPos][xPos + 1].getValue() == secondFree) || (tableBox[yPos][xPos - 1].getValue() == secondFree) ||
				(tableBox[yPos + 1][xPos].getValue() == secondFree) || (tableBox[yPos - 1][xPos].getValue() == secondFree)) &&
			(tableBox[yPos][xPos - 1].getValue() == "*"))
		{
			std::cout << "Second tile " << newTile.getSecond() << " = second free " << secondFree << std::endl;
			secondFree = newTile.getFirst();
			tableBox[yPos][xPos].setValue(newTile.getSecond());
			tableBox[yPos][xPos - 1].setValue(newTile.getFirst());
		} 
		else if ((newTile.getFirst() == firstFree) &&
			((tableBox[yPos][xPos + 1].getValue() == firstFree) || (tableBox[yPos][xPos - 1].getValue() == firstFree) ||
				(tableBox[yPos + 1][xPos].getValue() == firstFree) || (tableBox[yPos - 1][xPos].getValue() == firstFree)) &&
			(tableBox[yPos][xPos + 1].getValue() == "*"))
		{
			std::cout << "First tile " << newTile.getFirst() << " = first free " << firstFree << std::endl;
			firstFree = newTile.getSecond();
			tableBox[yPos][xPos].setValue(newTile.getFirst());
			tableBox[yPos][xPos + 1].setValue(newTile.getSecond());		
		}	
		else {
			std::cout << "xDown-yDown " << xPos << "-" << yPos << std::endl;
			std::cout << "tile second " << newTile.getSecond() << std::endl;
			std::cout << "tile first " << newTile.getFirst() << std::endl;
			std::cout << "table x+1 " << tableBox[yPos][xPos + 1].getValue() << std::endl;
			std::cout << "table x-1 " << tableBox[yPos][xPos - 1].getValue() << std::endl;
			std::cout << "table y+1 " << tableBox[yPos + 1][xPos].getValue() << std::endl;
			std::cout << "table y-1 " << tableBox[yPos - 1][xPos].getValue() << std::endl;
		}
	}

	std::cout << "First free: " << firstFree << " Second free: " << secondFree << std::endl;
}

bool Table::checkForPlacement(Tile playerTile, int xDown, int yDown, int xUp, int yUp) {
	int xPress =   (xDown - matrixX) / matrixPieceSize;
	int yPress =   (yDown - matrixY) / matrixPieceSize;
	int xUnpress = (xUp - matrixX)   / matrixPieceSize;
	int yUnpress = (yUp - matrixY)   / matrixPieceSize;
	std::cout << "xDown-yDown " << xPress << "-" << yPress << std::endl;

	if ((xPress == xUnpress) && (yPress == yUnpress) && (xPress - 1 >= 0) && (xPress + 1 <= 19) && (yPress - 1 >= 0) && (yPress + 1 <= 19))
	{
		if (tableBox[yPress][xPress].getValue() == "*" &&
			(playerTile.getFirst() == firstFree || playerTile.getFirst() == secondFree || playerTile.getSecond() == firstFree || playerTile.getSecond() == secondFree) &&
			((tableBox[yPress][xPress].getValue() == playerTile.getFirst() || tableBox[yPress][xPress].getValue() == playerTile.getSecond()) ||
				(tableBox[yPress][xPress + 1].getValue() == playerTile.getFirst() || tableBox[yPress][xPress + 1].getValue() == playerTile.getSecond()) ||
				(tableBox[yPress][xPress - 1].getValue() == playerTile.getFirst() || tableBox[yPress][xPress - 1].getValue() == playerTile.getSecond()) ||
				(tableBox[yPress + 1][xPress].getValue() == playerTile.getFirst() || tableBox[yPress + 1][xPress].getValue() == playerTile.getSecond()) ||
				(tableBox[yPress - 1][xPress].getValue() == playerTile.getFirst() || tableBox[yPress - 1][xPress].getValue() == playerTile.getSecond()))
			)
		{
			std::cout << "Add tile" << std::endl;
			addTile(playerTile, xPress, yPress);
			return true;
		}
	}

	return false;
}

//void Table::moveTileInLeft() {
//	Tile lastTile = tableTiles.back();
//
//	if (lastTile.getFirst() == lastTile.getSecond()) {
//		tableTiles.pop_back();
//		std::string lastCoord = tileYX.back();
//		tileYX.pop_back();
//		int xPos = 1;
//		int yPos = 1;
//
//		std::stringstream stream(lastCoord);
//		std::string temp;
//		int idx = 0;
//
//		while (std::getline(stream, temp, ',')) {
//			int value = std::stoi(temp);
//			if (idx == 0) {
//				yPos = value;
//				++idx;
//			}
//			else {
//				xPos = value;
//			}
//		}
//
//		//map[yPos][xPos] = lastTile.getSecond();
//		map[yPos][xPos - 1] = lastTile.getFirst();
//		map[yPos][xPos + 1] = "*";
//		std::stringstream ss;
//		ss << yPos << "," << (xPos - 1);
//		coordinates = ss.str();
//		tileYX.push_back(coordinates);
//
//		if (lastTile.getFirst() == firstFree) {
//			//firstFreePos["y"] = yPos;
//			firstFreePos["x"] = xPos - 1;
//		}
//		else {
//			//secondFreePos["y"] = yPos;
//			secondFreePos["x"] = xPos - 1;
//		}
//		
//		tableTiles.push_back(lastTile);
//		printMap();
//	}
//}

void Table::createMap() {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			//map[row][col] = "*";
			tableBox[row][col].setPosition(matrixX + col * matrixPieceSize, matrixY + row * matrixPieceSize);
		}
	}

	std::cout << "Map is created!" << std::endl;
}

void Table::render() {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			//map[row][col] = "*";
			tableBox[row][col].render();
		}
	}
}

void Table::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;

	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			//map[row][col] = "*";
			tableBox[row][col].setRenderer(_renderer);
		}
	}
}

void Table::clear()
{
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			//map[row][col] = "*";
			tableBox[row][col].setValue("*");
			
		}
	}
	firstTurn = true;
}
