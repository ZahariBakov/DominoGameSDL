#include "Table.h"

#include <iostream>
#include <sstream>

const int matrixX = 300;
const int matrixY = 10;
const int matrixPieceSize = 32;

//std::string coordinates;

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
		//map[yPos][xPos] = firstFree;
		//map[yPos + 1][xPos] = secondFree;
/*		firstFreePos["x"] = 9;
		firstFreePos["y"] = 9;
		secondFreePos["y"] = 10;
		secondFreePos["x"] = 9*/;
		//coordinates = "9,9";
		//tileYX.push_back(coordinates);
	}
	else 
	{
		//if ((newTile.getFirst() == firstFree && tableBox[yPos][xPos + 1].getValue() == "*")
		{
			//this->firstFree = newTile.getFirst();
			//this->secondFree = newTile.getSecond();
			tableBox[yPos][xPos].setValue(newTile.getFirst());
			tableBox[yPos][xPos + 1].setValue(newTile.getSecond());
		}
		
	}
	//else {
	//	if (newTile.getFirst() == firstFree && map[yPos][xPos + 1] == "*") {
	//		this->firstFree = newTile.getSecond();
	//		map[yPos][xPos] = newTile.getFirst();
	//		map[yPos][xPos + 1] = newTile.getSecond();
	//		std::stringstream ss;
	//		ss << yPos << "," << xPos;
	//		coordinates = ss.str();
	//		tileYX.push_back(coordinates);
	//		firstFreePos["x"] = xPos + 1;
	//		firstFreePos["y"] = yPos;
	//	}
	//	else if (newTile.getFirst() == secondFree && map[yPos][xPos + 1] == "*") {
	//		this->secondFree = newTile.getSecond();
	//		map[yPos][xPos] = newTile.getFirst();
	//		map[yPos][xPos + 1] = newTile.getSecond();
	//		std::stringstream ss;
	//		ss << yPos << "," << xPos;
	//		coordinates = ss.str();
	//		tileYX.push_back(coordinates);
	//		secondFreePos["y"] = yPos;
	//		secondFreePos["x"] = xPos + 1;
	//	}
	//	else if (newTile.getSecond() == firstFree && map[yPos][xPos - 1] == "*") {
	//		this->firstFree = newTile.getFirst();
	//		map[yPos][xPos] = newTile.getSecond();
	//		map[yPos][xPos - 1] = newTile.getFirst();
	//		std::stringstream ss;
	//		ss << yPos << "," << (xPos - 1);
	//		coordinates = ss.str();
	//		tileYX.push_back(coordinates);
	//		firstFreePos["x"] = xPos - 1;
	//		firstFreePos["y"] = yPos;
	//	}
	//	else if (newTile.getSecond() == secondFree && map[yPos][xPos - 1] == "*") {
	//		this->secondFree = newTile.getFirst();
	//		map[yPos][xPos] = newTile.getSecond();
	//		map[yPos][xPos - 1] = newTile.getFirst();
	//		std::stringstream ss;
	//		ss << yPos << "," << (xPos - 1);
	//		coordinates = ss.str();
	//		tileYX.push_back(coordinates);
	//		secondFreePos["y"] = yPos;
	//		secondFreePos["x"] = xPos - 1;
	//	}
	//}

	//this->tableTiles.push_back(newTile);
	//std::cout << "First free piece of tile is: " << firstFree << std::endl;
	//std::cout << "Second free piece of tile is: " << secondFree << std::endl;
	//std::cout << "First free pos [" << firstFreePos["x"] << "][" << firstFreePos["y"] << "]\n";
	//std::cout << "Second free pos [" << secondFreePos["x"] << "][" << secondFreePos["y"] << "]\n";
	//std::cout << "Table add tile." << std::endl;
	//printMap();
}

//void Table::printMap() const {
//	for (int row = 0; row < 20; ++row) {
//		for (int col = 0; col < 20; ++col) {
//			std::cout << map[row][col];
//		}
//		std::cout << std::endl;
//	}
//}

void Table::checkForPlacement(Tile playerTile, int xDown, int yDown, int xUp, int yUp, int &xPos, int &yPos) {
	int xPress =   (xDown - matrixX) / matrixPieceSize;
	int yPress =   (yDown - matrixY) / matrixPieceSize;
	int xUnpress = (xUp - matrixX)   / matrixPieceSize;
	int yUnpress = (yUp - matrixY)   / matrixPieceSize;

	////std::cout << "down - up x: " << xPress << "-" << xUnpress << std::endl;
	////std::cout << "down - up y: " << yPress << "-" << yUnpress << std::endl;

	//if (xPress == xUnpress && yPress == yUnpress) {
	//	if (playerTile.getFirst() == firstFree || playerTile.getSecond() == firstFree) {
	//		std::cout << "first free is with pos X,Y: " << firstFreePos["x"] << " " << firstFreePos["y"] << std::endl;

	//		if ((xPress == firstFreePos["x"] - 1 || xPress == firstFreePos["x"] + 1 || xPress == firstFreePos["x"]) && (yPress == firstFreePos["y"]) ||
	//			((yPress == firstFreePos["y"] - 1 || yPress == firstFreePos["y"] + 1 || yPress == firstFreePos["y"]) && (xPress == firstFreePos["x"]))) {
	//			if (map[yPress][xPress] == "*") {
	//				std::cout << "can add tile here: [" << xPress << "][" << yPress << "]" << std::endl;
	//				xPos = xPress;
	//				yPos = yPress;
	//				addTile(playerTile, xPress, yPress);
	//				std::cout << "First free is: " << firstFree << "\n";
	//				std::cout << "Second free is: " << secondFree << std::endl;
	//			}
	//		}
	//	}

	if (tableBox[yPress][xPress].getValue() == "*" && tableBox[yPress][xPress + 1].getValue() == "*" 
		&& ((tableBox[yPress][xPress].getValue() == playerTile.getFirst() || tableBox[yPress][xPress].getValue() == playerTile.getSecond()) ||
			(tableBox[yPress][xPress + 1].getValue() == playerTile.getFirst() || tableBox[yPress][xPress + 1].getValue() == playerTile.getSecond()) ||
				(tableBox[yPress][xPress - 1].getValue() == playerTile.getFirst() || tableBox[yPress][xPress - 1].getValue() == playerTile.getSecond()) ||
					(tableBox[yPress + 1][xPress].getValue() == playerTile.getFirst() || tableBox[yPress + 1][xPress].getValue() == playerTile.getSecond()) ||
						(tableBox[yPress - 1][xPress].getValue() == playerTile.getFirst() || tableBox[yPress - 1][xPress].getValue() == playerTile.getSecond())))
	{
		addTile(playerTile, xPress, yPress);
	}
		//if (playerTile.getFirst() == secondFree || playerTile.getSecond() == secondFree) {
		//	std::cout << "second free is with pos X,Y: " << secondFreePos["x"] << " " << secondFreePos["y"] << std::endl;

		//	if ((xPress == secondFreePos["x"] - 1 || xPress == secondFreePos["x"] + 1 || xPress == secondFreePos["x"]) && (yPress == secondFreePos["y"]) ||
		//		((yPress == secondFreePos["y"] - 1 || yPress == secondFreePos["y"] + 1 || yPress == secondFreePos["y"]) && (xPress == secondFreePos["x"]))) {
		//		if (map[yPress][xPress] == "*") {
		//			std::cout << "can add tile here: [" << xPress << "][" << yPress << "]" << std::endl;
		//			xPos = xPress;
		//			yPos = yPress;
		//			addTile(playerTile, xPress, yPress);
		//			std::cout << "First free is: " << firstFree << "\n";
		//			std::cout << "Second free is: " << secondFree << std::endl;
		//		}
		//	}
		//}
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

	std::cout << "map is created" << std::endl;
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
