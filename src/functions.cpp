#pragma once
#include "Utility.cpp"
bool checkMove(std::string);
void addOccupiedDirection(int, std::vector<int>&, Direction);
sf::Vector2f getPositionFromIndex(int);
int getIndexFromPos(sf::Vector2f);
int getColumnFromIndex(int);
int getRowFromIndex(int);
bool isKingInCheck(bool);
sf::Vector2f coord(char, char);
void move(std::string);
bool isLegalMove(std::string);
void back();
void loadPosition();
std::string chessSquare(sf::Vector2f);
std::vector<int> getOccupiedSquares(bool);
//Position to Index
inline std::string codetostring(int code) {
	std::vector<std::string> arr = { "Rook","Knight","Bishop","Queen","King","Pawn"};
	return arr[code - 1];
}
inline static int Promotion(bool isWhite) {
	sf::Texture pieces, tboard;
	sf::RectangleShape rect;
	sf::Color color = sf::Color::Black;
	float xOffset=0;
	color.a = 90;
	rect.setFillColor(color);
	rect.setSize(sf::Vector2f(720, 720));
	rect.setPosition(0, 0);

	pieces.loadFromFile("Assets/figures.png");
	tboard.loadFromFile("Assets/Chessboard.png");
	sf::Sprite queen(pieces), rook(pieces), bishop(pieces), knight(pieces);
	int qcode = 4, kcode = 2, bcode = 3, rcode = 1;
	int y = isWhite?1:0;
	queen.setTextureRect(sf::IntRect(int(size * 3), int(size_y * y), int(size), int(size_y)));
	rook.setTextureRect(sf::IntRect(0, int(size_y * y), int(size), int(size_y)));
	bishop.setTextureRect(sf::IntRect(int(size * 2), int(size_y * y), int(size), int(size_y)));
	knight.setTextureRect(sf::IntRect(int(size), int(size_y * y), int(size), int(size_y)));
	float dist = (window.getSize().x / 4);
	queen.setPosition(sf::Vector2f(dist-125,300));
	queen.setScale(sf::Vector2f(1.5, 1.5));
	rook.setPosition(sf::Vector2f((dist * 2)-125, 300));
	rook.setScale(sf::Vector2f(1.5, 1.5));
	bishop.setPosition(sf::Vector2f((dist * 3)-125, 300));
	bishop.setScale(sf::Vector2f(1.5, 1.5));
	knight.setPosition(sf::Vector2f((dist * 4)-125, 300));
	knight.setScale(sf::Vector2f(1.5, 1.5));
	sf::RectangleShape piecerect(sf::Vector2f(110, 110));
	piecerect.setFillColor(color);
	sf::Sprite sBoard(tboard);
	std::vector<sf::Sprite> pieceList = { queen,rook,bishop,knight }; 
	sBoard.setScale(0.53f, 0.53f);
	bool chosen = false;
	while (!chosen) {
		bool clicked = false;
		sf::Vector2i pos = sf::Mouse::getPosition();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			}break;
			case sf::Event::MouseButtonPressed: {
				if (event.key.code == sf::Mouse::Left) {
					clicked = true;
				}
			}break;
			case sf::Event::Resized: {
				float newWidth = static_cast<float>(event.size.width);
				float newHeight = 720.f;
				sf::View view(sf::FloatRect(0, 0, newWidth, newHeight));
				xOffset = (newWidth - window.getSize().y) / 2.0f;
				float yOffset = 0;// (newWidth - window.getSize().x) / 2.0f;
				view.move(-xOffset, -yOffset);
				window.setView(view);
			}break;
			default: {
				break;
			}
			}


		}
		pos = sf::Mouse::getPosition();
		piecerect.setPosition(-100, -100);
		int i = 0;
		for (sf::Sprite p : pieceList) {

			if (p.getGlobalBounds().contains(pos.x - (dist * 2)+20, pos.y)) {
				piecerect.setPosition(p.getPosition());
			}
			if (clicked && p.getGlobalBounds().contains(pos.x - (dist * 2) + 20, pos.y)) {
				switch (i)
				{
				case 0: {
					return isWhite ? 4 : -4;
				}break;
				case 1: {
					return isWhite ? 1 : -1;
				}break;
				case 2: {
					return isWhite ? 3 : -3;
				}break;
				case 3: {
					return isWhite ? 2 : -2;
				}break;
				default: {
					break;
				}
				}
			}
			i++;
		}
		window.clear();
		window.draw(sBoard);
		window.draw(rect);
		window.draw(piecerect);
		window.draw(rook);
		window.draw(knight);
		window.draw(bishop);
		window.draw(queen);
		window.display();

	}
	return 0;
}
//Returns legal squares of a piece
std::vector<Square> getLegalSquares(Piece &piece_) {
	std::vector<Square> legalsq = {};
	if (piece->square.square == "null") {
		return legalsq;
	}
	Square mov_square;
	int index = getIndexFromPos(piece_.sprite.getPosition());
	if (index < 0 || index > 63) {
		return legalsq;
	}
	switch (abs(piece_.code))
	{
	case PAWN: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		//Two square move
		std::string newSquare = chessSquare(sf::Vector2f(coord(piece_.square.square[0], piece_.square.square[1]).x, coord(piece_.square.square[0], piece_.square.square[1]).y + (piece_.isWhite ? -int(pos_size * 2) : int(pos_size * 2))));//two square Move
		std::string str = oldSquare + newSquare;
		if (isLegalMove(str)) {
			mov_square.square = newSquare;
			mov_square.pos = coord(newSquare[0], newSquare[1]);
			legalsq.push_back(mov_square);
		}

		//one square move
		newSquare = chessSquare(sf::Vector2f(piece_.sprite.getPosition().x, piece_.sprite.getPosition().y + (piece_.isWhite ? -int(pos_size) : int(pos_size))));
		str = oldSquare + newSquare;
		bool isPromotion=false;
		if (newSquare[1] == piece_.isWhite ? '8' : '1') {
			sf::Vector2f newPos = coord(newSquare[0], newSquare[1]);
			sf::Vector2f oldPos = coord(oldSquare[0], oldSquare[1]);
			isPromotion = true;
			if (checkMove(str)) {
				piece_.sprite.setPosition(newPos);
				if (!isKingInCheck(piece_.isWhite)) {
					mov_square.square = newSquare;
					mov_square.pos = newPos;
					legalsq.push_back(mov_square);
				}
				piece_.sprite.setPosition(oldPos);
			}
		}
		if (!isPromotion) 
			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}

		//one cross_right
		newSquare = chessSquare(sf::Vector2f(piece_.sprite.getPosition().x + int(pos_size), piece_.sprite.getPosition().y + (piece_.isWhite ? -int(pos_size) : int(pos_size))));
		str = oldSquare + newSquare;
		isPromotion = false;
		if (newSquare[1] == (piece_.isWhite ? '8' : '1')) {
			sf::Vector2f newPos = coord(newSquare[0], newSquare[1]);
			sf::Vector2f oldPos = coord(oldSquare[0], oldSquare[1]);
			isPromotion = true;
			if (checkMove(str)) {
				piece_.sprite.setPosition(newPos);
				if (!isKingInCheck(piece_.isWhite)) {
					mov_square.square = newSquare;
					mov_square.pos = newPos;
					legalsq.push_back(mov_square);
				}
				piece_.sprite.setPosition(oldPos);
			}
			
		}
		if (!isPromotion) {
			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}

		//one cross_left
		newSquare = chessSquare(sf::Vector2f(piece_.sprite.getPosition().x - int(pos_size), piece_.sprite.getPosition().y + (piece_.isWhite ? -int(pos_size) : int(pos_size))));
		str = oldSquare + newSquare;
		isPromotion = false;
		if (newSquare[1] == (piece_.isWhite ? '8' : '1')) {
			sf::Vector2f newPos = coord(newSquare[0], newSquare[1]);
			sf::Vector2f oldPos = coord(oldSquare[0], oldSquare[1]);
			isPromotion = true;
			if (checkMove(str)) {
				piece_.sprite.setPosition(newPos);
				if (!isKingInCheck(piece_.isWhite)) {
					mov_square.square = newSquare;
					mov_square.pos = newPos;
					legalsq.push_back(mov_square);
				}
				piece_.sprite.setPosition(oldPos);
			}
		}
		if (!isPromotion) {
			if (isLegalMove(str)) { 
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	case ROOK: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		std::string newSquare;
		std::vector<int> occupiedSquares = {};
		int index = getIndexFromPos(piece_.sprite.getPosition());
		//TOP
		Direction direction = TOP;
		addOccupiedDirection(index, occupiedSquares, direction);
		//BOTTOM
		direction = BOTTOM;
		addOccupiedDirection(index, occupiedSquares, direction);
		//LEFT
		direction = LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//RIGHT
		direction = RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);

		std::string str;
		for (int occsq : occupiedSquares) {
			newSquare = chessSquare(getPositionFromIndex(occsq));
			str = oldSquare + newSquare;

			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	case KNIGHT: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		std::string newSquare;
		int index = getIndexFromPos(piece_.sprite.getPosition());
		std::vector<int> occupiedSquares = {};
		if (getColumnFromIndex(index) > 2 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + 6);
		if (getColumnFromIndex(index) < 7 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + 10);
		if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) < 7)occupiedSquares.push_back(index + 15);
		if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) < 7)occupiedSquares.push_back(index + 17);
		if (getColumnFromIndex(index) < 7 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index - 6);
		if (getColumnFromIndex(index) > 2 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index - 10);
		if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) > 2)occupiedSquares.push_back(index - 15);
		if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) > 2)occupiedSquares.push_back(index - 17);
		std::string str;
		for (int occsq : occupiedSquares) {
			newSquare = chessSquare(getPositionFromIndex(occsq));
			str = oldSquare + newSquare;

			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	case KING: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		std::string newSquare;
		int index = getIndexFromPos(piece_.sprite.getPosition());
		std::vector<int> occupiedSquares = {};
		if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) < 8) occupiedSquares.push_back(index + BOTTOM_LEFT);
		if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP_LEFT);
		if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + BOTTOM_RIGHT);
		if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP_RIGHT);
		if (getRowFromIndex(index) < 8)occupiedSquares.push_back(index + BOTTOM);
		if (getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP);
		if (getColumnFromIndex(index) < 8)occupiedSquares.push_back(index + RIGHT);
		if (getColumnFromIndex(index) == 5)occupiedSquares.push_back(index + RIGHT*2);
		if (getColumnFromIndex(index) > 1)occupiedSquares.push_back(index + LEFT);
		if (getColumnFromIndex(index) == 5) { 
			occupiedSquares.push_back(index + LEFT * 2); 
			occupiedSquares.push_back(index + LEFT * 3);
		}
		std::string str;
		for (int occsq : occupiedSquares) {
			newSquare = chessSquare(getPositionFromIndex(occsq));
			str = oldSquare + newSquare;

			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	case BISHOP: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		std::string newSquare;
		int index = getIndexFromPos(piece_.sprite.getPosition());
		std::vector<int> occupiedSquares = {};
		
		//top left
		Direction direction = TOP_LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//bottom left
		direction = BOTTOM_LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//bottom right
		direction = BOTTOM_RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//top right
		direction = TOP_RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);
		std::string str;
		for (int occsq : occupiedSquares) {
			newSquare = chessSquare(getPositionFromIndex(occsq));
			str = oldSquare + newSquare;

			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	case QUEEN: {
		std::string oldSquare = chessSquare(piece_.sprite.getPosition());
		std::string newSquare;
		int index = getIndexFromPos(piece_.sprite.getPosition());
		std::vector<int> occupiedSquares = {};
		//top right
		Direction direction = TOP_RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//top left
		direction = TOP_LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//bottom left
		direction = BOTTOM_LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//bottom right
		direction = BOTTOM_RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//TOP
		direction = TOP;
		addOccupiedDirection(index, occupiedSquares, direction);
		//BOTTOM
		direction = BOTTOM;
		addOccupiedDirection(index, occupiedSquares, direction);
		//LEFT
		direction = LEFT;
		addOccupiedDirection(index, occupiedSquares, direction);
		//RIGHT
		direction = RIGHT;
		addOccupiedDirection(index, occupiedSquares, direction);
		std::string str;
		for (int occsq : occupiedSquares) {
			newSquare = chessSquare(getPositionFromIndex(occsq));
			str = oldSquare + newSquare;

			if (isLegalMove(str)) {
				mov_square.square = newSquare;
				mov_square.pos = coord(newSquare[0], newSquare[1]);
				legalsq.push_back(mov_square);
			}
		}
	}break;
	default:
		break;
	}
	return legalsq;
}
//Position to index
inline int getIndexFromPos(sf::Vector2f pos) {
	pos -= additional;
	int x = int(pos.x / pos_size);
	int y = int(pos.y / pos_size);
	int index = (y * 8) + x;
	return index;
}
//Checks if king of given color is in check
inline bool isKingInCheck(bool isWhite) {
	const int kingIndex = isWhite ? 28 : 4;
	std::vector<int> occsq = getOccupiedSquares(!isWhite);
	for (int i = 0; i < occsq.size(); i++) {
		if (occsq[i] == getIndexFromPos(piece[kingIndex].sprite.getPosition())) return 1;
	}

	return 0;
}
//Index to Row
inline int getRowFromIndex(int index) {
	int row = (int)(index / 8);
	row++;
	if (row > 8)
		row = 8;

	return row;
}
//Checks if given index(of square index) is Occupied or not
inline bool isSquareOccupied(int index) {
	for (int i = 0; i < 32; i++) {
		if (getIndexFromPos(piece[i].sprite.getPosition()) == index) {
			if ((i == selected) && isMove) continue;
			return true;
		}
	}
	return false;
}
//Checks if given position(of square) is Occupied or not
inline bool isSquareOccupied(sf::Vector2f pos) {
	for (int i = 0; i < 32; i++) {
		if (piece[i].sprite.getPosition() == pos) {
			if ((i == selected) && isMove) continue;
			return true;
		}
	}
	return false;
}
//Index to Column
inline int getColumnFromIndex(int index) {
	int row = getRowFromIndex(index);
	index -= ((row - 1) * 8);
	return index + 1;
}
//Adds Non-Occupied squares of given direction in a given array
inline void addOccupiedDirection(int index, std::vector<int>& occsq, Direction dir) {
	bool isDiagonal = true;
	if (dir == TOP || dir == BOTTOM || dir == LEFT || dir == RIGHT) {
		isDiagonal = false;
	}
	if (isDiagonal) {
		int x_limit = 1, y_limit = 1;
		if (dir == TOP_LEFT) {
			x_limit = 1;
			y_limit = 1;
		}
		else if (dir == TOP_RIGHT) {
			x_limit = 8;
			y_limit = 1;
		}
		else if (dir == BOTTOM_LEFT) {
			x_limit = 1;
			y_limit = 8;
		}
		else if (dir == BOTTOM_RIGHT) {
			x_limit = 8;
			y_limit = 8;
		}
		int temp_index = index + dir;
		while (getColumnFromIndex(temp_index - dir) != x_limit && getRowFromIndex(temp_index - dir) != y_limit) {
			if (isSquareOccupied(temp_index)) {
				occsq.push_back(temp_index);
				break;
			}
			occsq.push_back(temp_index);
			temp_index += dir;
		}
	}
	else {
		bool isVertical = false;
		if (dir == TOP || dir == BOTTOM) {
			isVertical = true;
		}
		int temp_index = index + dir;
		if (isVertical) {
			while (getRowFromIndex(temp_index - dir) != (dir == TOP ? 1 : 8)) {
				if (isSquareOccupied(temp_index)) {
					occsq.push_back(temp_index);
					break;
				}
				occsq.push_back(temp_index);
				temp_index += dir;

			}
		}
		else {
			while (getColumnFromIndex(temp_index - dir) != (dir == LEFT ? 1 : 8)) {
				if (isSquareOccupied(temp_index)) {
					occsq.push_back(temp_index);
					break;
				}
				occsq.push_back(temp_index);
				temp_index += dir;

			}
		}
	}
	std::sort(occsq.begin(), occsq.end());
	occsq.erase(std::unique(occsq.begin(), occsq.end()), occsq.end());
}
//Index to Position
inline sf::Vector2f getPositionFromIndex(int index) {
	int row = getRowFromIndex(index);
	int col = getColumnFromIndex(index);
	row--, col--;

	sf::Vector2f pos = sf::Vector2f(col * pos_size, row * pos_size) + additional;
	return pos;
}
//Initalizes the game
inline void initGame() {
	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			square[k].pos = sf::Vector2f(pos_size * j, pos_size * i) + additional;
			square[k].square = chessSquare(square[k].pos);
			k++;
		}
	}
	k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			piece[k].isWhite = bool(y);
			piece[k].code = n;
			piece[k].isFirst = true;
			piece[k].sprite.setTextureRect(sf::IntRect(int(size * x), int(size_y * y), int(size), int(size_y)));
			piece[k].sprite.setPosition(sf::Vector2f(pos_size * j, pos_size * i) + additional);
			piece[k].sprite.setScale(sf::Vector2f(scale, scale));
			k++;
		}

	}
}
//Main notation string which is loaded every frame
std::string position = "";

//Loads Position (called every move)
inline void loadPosition() {
	score = 0;
	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			piece[k].isWhite = bool(y);
			piece[k].isFirst = true;
			piece[k].code = n;
			piece[k].sprite.setTextureRect(sf::IntRect(int(size * x), int(size_y * y), int(size), int(size_y)));
			piece[k].sprite.setPosition(sf::Vector2f(pos_size * j, pos_size * i) + additional);
			piece[k].sprite.setScale(sf::Vector2f(scale, scale));
			k++;
		}
	}
	for (int i = 0; i < int(position.length()); i += 5) {
		currentmove = int(i / 5);
		move(position.substr(i, 4));
	} 
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 64; j++) {
			if (square[j].square == chessSquare(piece[i].sprite.getPosition())) {
				piece[i].square = square[j];
				break;
			}
		}
	}
	
}
//Position to Notation
inline std::string chessSquare(sf::Vector2f p) {
	p -= additional;
	std::string s = "";
	s += char(p.x / pos_size + 97);
	s += char(7 - (p.y / pos_size) + 49);
	return s;
}
//to reset game
inline void resetGame() {
	position.erase(0, position.length());
	loadPosition();
	isWhiteTurn = true;
}
//Reverses Previous Move
inline void back() {
	if (int(position.length())) {
		position.erase(position.length() - 5, 5);
		isWhiteTurn = !isWhiteTurn;
		loadPosition();
	}
}
//Notation to Poition
inline sf::Vector2f coord(char a, char b) {
	int x = (int(a) - 97);
	int y = (7 - int(b) + 49);
	sf::Vector2f result = (sf::Vector2f(x * pos_size, y * pos_size) + additional);
	return result;
}
//Code to score
//Negative for white
int toScore(int code) {
	int number = 0;
	bool isWhite = code > 0 ? true : false;
	switch (abs(code)) {
	case ROOK: {
		number = 5;
	}break;
	case KNIGHT: {
		number = 3;
	}break;
	case BISHOP: {
		number = 3;
	}break;
	case QUEEN: {
		number = 9;
	}break;
	case KING: {
		number = 0;
	}break;
	case PAWN: {
		number = 1;
	}break;
	default: {
		number = 0;
	}
	}
	if (isWhite) number = -number;

	return number;
}
//Moves given notation as string
inline void move(std::string str) {
	sf::Vector2f oldPos = coord(str[0], str[1]);
	sf::Vector2f newPos = coord(str[2], str[3]);

	int movedPiece = -10;
	bool occupiedPiece = false;

	//Capture
	for (int i = 0; i < 32; i++) {
		if (piece[i].sprite.getPosition() == newPos) {
			piece[i].sprite.setPosition(-100, -100);
			score += toScore(piece[i].code); 
			piece[i].square.square = "null";
			occupiedPiece = true;
		}
	}

	//Moving Piece
	for (int i = 0; i < 32; i++) {
		if (piece[i].sprite.getPosition() == oldPos) {
			movedPiece = i;
			if (abs(piece[i].code) == PAWN || abs(piece[i].code) == ROOK || abs(piece[i].code) == KING) {
				piece[i].isFirst = false;
			}
			piece[i].sprite.setPosition(newPos);
		}
	}
	if (abs(piece[movedPiece].code) == PAWN) {
		// Promotion
		if (str[3] == (piece[movedPiece].isWhite ? '8' : '1')) {
			int row = getRowFromIndex(movedPiece);
			int column = getColumnFromIndex(movedPiece);
			row--, column--;
			int code;
			bool isPlayed = false;
			for (Move imove : moves) {
				if (imove.move == currentmove) {
					isPlayed = true;
					code = imove.code;
					break;
				}
			}
			if(!isPlayed) {
				code = Promotion(piece[movedPiece].isWhite);
				Move addMove;
				addMove.code = code;
				addMove.move = currentmove;
				moves.push_back(addMove);
			}
			//board[row][column] = code;
			piece[movedPiece].code = code;
			int x = abs(code) - 1;
			int y = code > 0 ? 1 : 0;
			piece[movedPiece].sprite.setTextureRect(sf::IntRect(int(size * x), int(size_y * y), int(size), int(size_y)));
			score -= toScore(code);

		}
		//en passant
		else if (abs(oldPos.x - newPos.x) == int(pos_size)) {
			if (str[3] == (piece[movedPiece].isWhite ? '6' : '3')) {
				for (int i = 0; i < 32; i++) {
					if ((piece[i].sprite.getPosition() == sf::Vector2f(newPos.x, oldPos.y)) && abs(piece[i].code) == PAWN) {
						bool isEnpassant = true;
						if (occupiedPiece) {
							isEnpassant = false;
							break;
						}
						if (isEnpassant) {
							piece[i].sprite.setPosition(-100, -100);
							piece[i].square.square = "null";
							score += toScore(piece[i].code);
							break;
						}
					}
				}
			}
		}
	}

	if (abs(piece[movedPiece].code) == KING) {
		//castle movement
		if (str == "e1g1" || str == "e1h1") {
			piece[28].sprite.setPosition(coord('g', '1'));
			piece[31].sprite.setPosition(coord('f', '1'));
		}
		else if (str == "e1a1" || str == "e1b1" || str == "e1c1") {
			piece[28].sprite.setPosition(coord('c', '1'));
			piece[24].sprite.setPosition(coord('d', '1'));
		}
		else if (str == "e8g8" || str == "e8h8") {
			piece[4].sprite.setPosition(coord('g', '8'));
			piece[7].sprite.setPosition(coord('f', '8'));
			piece[7].square.square = "f8";
		}
		else if (str == "e8a8" || str == "e8b8" ||str == "e8c8") {
			piece[4].sprite.setPosition(coord('c', '8'));
			piece[0].sprite.setPosition(coord('d', '8'));
		}
	}
}
//Returns occupied squares of given color
inline std::vector<int> getOccupiedSquares(bool White) {
	std::vector<int> occupiedSquares = {};
	int index = -10;
	int start = 0, end = 0;
	if (White) {
		start = 16, end = 32;
	}
	else {
		start = 0, end = 16;
	}
	for (int i = start; i < end; i++) {
		if (piece[i].square.square == "null") continue;
		switch (abs(piece[i].code)) {
		case PAWN: {
			index = getIndexFromPos(piece[i].sprite.getPosition());
			if (getColumnFromIndex(index) > 1)occupiedSquares.push_back(index + (White ? TOP_LEFT : BOTTOM_LEFT));
			if (getColumnFromIndex(index) < 8)occupiedSquares.push_back(index + (White ? TOP_RIGHT : BOTTOM_RIGHT));

		}break;
		case KNIGHT: {
			index = getIndexFromPos(piece[i].sprite.getPosition());
			if (getColumnFromIndex(index) > 2 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + 6);
			if (getColumnFromIndex(index) < 7 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + 10);
			if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) < 7)occupiedSquares.push_back(index + 15);
			if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) < 7)occupiedSquares.push_back(index + 17);
			if (getColumnFromIndex(index) < 7 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index - 6);
			if (getColumnFromIndex(index) > 2 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index - 10);
			if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) > 2)occupiedSquares.push_back(index - 15);
			if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) > 2)occupiedSquares.push_back(index - 17);

		}break;
		case KING: {
			index = getIndexFromPos(piece[i].sprite.getPosition());
			if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) < 8) occupiedSquares.push_back(index + BOTTOM_LEFT);
			if (getColumnFromIndex(index) > 1 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP_LEFT);
			if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) < 8)occupiedSquares.push_back(index + BOTTOM_RIGHT);
			if (getColumnFromIndex(index) < 8 && getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP_RIGHT);
			if (getRowFromIndex(index) < 8)occupiedSquares.push_back(index + BOTTOM);
			if (getRowFromIndex(index) > 1)occupiedSquares.push_back(index + TOP);
			if (getColumnFromIndex(index) < 8)occupiedSquares.push_back(index + RIGHT);
			if (getColumnFromIndex(index) > 1)occupiedSquares.push_back(index + LEFT);

		}break;
		case BISHOP: {
			int index = getIndexFromPos(piece[i].sprite.getPosition());
			//top right
			Direction direction = TOP_RIGHT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//top left
			direction = TOP_LEFT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//bottom left
			direction = BOTTOM_LEFT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//bottom right
			direction = BOTTOM_RIGHT;
			addOccupiedDirection(index, occupiedSquares, direction);

		}break;
		case ROOK: {
			int index = getIndexFromPos(piece[i].sprite.getPosition());
			//TOP
			addOccupiedDirection(index, occupiedSquares, TOP);
			//BOTTOM
			addOccupiedDirection(index, occupiedSquares, BOTTOM);
			//LEFT
			addOccupiedDirection(index, occupiedSquares, LEFT);
			//RIGHT
			addOccupiedDirection(index, occupiedSquares, RIGHT);

		}break;
		case QUEEN: {
			int index = getIndexFromPos(piece[i].sprite.getPosition());
			//TOP
			Direction direction = TOP;
			addOccupiedDirection(index, occupiedSquares, direction);
			//BOTTOM
			direction = BOTTOM;
			addOccupiedDirection(index, occupiedSquares, direction);
			//LEFT
			direction = LEFT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//RIGHT
			direction = RIGHT;
			addOccupiedDirection(index, occupiedSquares, direction);

			//top right
			direction = TOP_RIGHT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//top left
			direction = TOP_LEFT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//bottom right
			direction = BOTTOM_RIGHT;
			addOccupiedDirection(index, occupiedSquares, direction);
			//bottom left
			direction = BOTTOM_LEFT;
			addOccupiedDirection(index, occupiedSquares, direction);

		}break;
		}
	}
	return occupiedSquares;
}
std::string fenPosition() {
	std::string fen = "";
	std::unordered_map<int,std::string> piece_map= {
		{KING,"K"},
		{QUEEN,"Q"},
		{ROOK,"R"},
		{KNIGHT,"N"},
		{BISHOP,"B"},
		{PAWN,"P"},
		{-KING,"k"},
		{-QUEEN,"q"},
		{-ROOK,"r"},
		{-KNIGHT,"n"},
		{-BISHOP,"b"},
		{-PAWN,"p"}
	};
	for (int rows = 1; rows <= 8; rows++) {
		int counter = 0;
		for (int cols = 1; cols <= 8; cols++) {
			int index = (((rows - 1) * 8) + (cols - 1));
			sf::Vector2f pos = getPositionFromIndex(index);
			int piece_occ = -10;
			for (int i = 0; i < 64; i++) {
				if (pos == piece[i].sprite.getPosition()) {
					piece_occ = i;
					break;
				}
			}
			if (piece_occ == -10) {
				counter++;
				if (cols != 8)
					continue;
				else
					fen += std::to_string(counter);
			}
			else {
				if (counter != 0) {
					fen += std::to_string(counter);
					counter = 0;
				}

				fen += piece_map[piece[piece_occ].code];
			}
		}
		if(rows != 8)
			fen += "/";
	}
	//turn
	fen += isWhiteTurn ? " w " : " b ";

	//Castle rights
	if (!piece[28].isFirst && !piece[4].isFirst) {
		fen += "- ";
	}
	else {
		if (piece[28].isFirst && piece[31].isFirst)
			fen += "K";
		
		if (piece[28].isFirst && piece[24].isFirst) 
			fen += "Q";

		if (piece[4].isFirst && piece[7].isFirst)
			fen += "k";

		if (piece[4].isFirst && piece[0].isFirst)
			fen += "q";

		if (!piece[0].isFirst && !piece[7].isFirst && !piece[24].isFirst && !piece[31].isFirst) 
			fen += "- ";
		else 
			fen += " ";
		
	}
	//en passant availability
	if (en_passant == "null") {
		fen += "- ";
	}
	else {
		fen += en_passant + " ";
	}

	//halfmove clock
	fen += std::to_string(halfmovec) + " ";


	//fullmove counter
	fen += std::to_string(fullmovec);
	return fen;
}
inline bool isLegalMove(std::string str) {
	sf::Vector2f oldPos = coord(str[0], str[1]);
	sf::Vector2f newPos = coord(str[2], str[3]);
	if (oldPos != newPos) {
		position += str + " ";
		if (checkMove(str)) {
			isWhiteTurn = !isWhiteTurn;
			loadPosition();
			if (isKingInCheck(!isWhiteTurn)) {
				back();
				loadPosition();
				return 0;
			}
			back();
			loadPosition();
			return 1;
		}
		back();
		isWhiteTurn = !isWhiteTurn;
		loadPosition();
		return 0;
	}
	return 0;
}