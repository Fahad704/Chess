#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <unordered_map>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"

#pragma warning(disable : 4996)

//classes

class Move {
public:
	int move;
	int code;
};

class Square {
public:
	std::string square;
	sf::Vector2f pos;
};

class Piece {
public:
	bool isWhite;
	int code;
	sf::Sprite sprite;
	Square square;
	bool isFirst;
};

//enums

enum GameMode {
	GM_GAMEPLAY,
	GM_MENU,
};
enum {
	NOTHING,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN
};
enum Direction {
	TOP_LEFT = -9,
	TOP,
	TOP_RIGHT,
	LEFT = -1,
	RIGHT = 1,
	BOTTOM_LEFT = 7,
	BOTTOM,
	BOTTOM_RIGHT
};

//Sizes

const float pos_size = 86.f;//distance between 2 squares in board
const float size = 69.f;//width of piece rect from figures.jpg
const float size_y = 74.f;//height of piece rect
const float scale = 1.0f;//Piece scale
const sf::Vector2f additional = sf::Vector2f(33.f, 10.f);//additional vector to push pieces to set on board

//Values

int score = 0;
int currentmove = 0;
int selected = -10;//current selected piece index(if selected)
std::string en_passant = "null";
int halfmovec = 0;
int fullmovec = 1;
int gameover = 0;
GameMode gamemode = GM_MENU;

//bools
bool isMove = false;
bool leftClicked = false;
bool isWhiteTurn = true;
bool board_changed = false;
bool isCapture = false;
bool isLogOn = true;

//objects

Square square[64];
Piece piece[32];
std::vector<Move> moves; 

//window
sf::RenderWindow window(sf::VideoMode(720, 720), "Chess!");


//Boards

int board[8][8] = {
	-1,-2,-3,-4,-5,-3,-2,-1,
	-6,-6,-6,-6,-6,-6,-6,-6,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 6, 6, 6, 6, 6, 6, 6, 6,
	 1, 2, 3, 4, 5, 3, 2, 1,
};
int startingPos[8][8] = {
	-1,-2,-3,-4,-5,-3,-2,-1,
	-6,-6,-6,-6,-6,-6,-6,-6,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 6, 6, 6, 6, 6, 6, 6, 6,
	 1, 2, 3, 4, 5, 3, 2, 1,
};