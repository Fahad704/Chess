#pragma once
//Checks if given move as old position and new position is a "rook move or not"
inline static bool isRookMove(sf::Vector2f oldPos, sf::Vector2f newPos) {
	enum {
		VERTICAL,
		HORIZONTAL
	};
	int move_dir;
	int distance;
	if (newPos.x - oldPos.x == 0 && (int(newPos.y - oldPos.y) % int(pos_size)) == 0) {
		move_dir = VERTICAL;
		distance = ((oldPos.y - newPos.y) / pos_size);
	}
	else if (newPos.y - oldPos.y == 0 && (int(newPos.x - oldPos.x) % int(pos_size)) == 0) {
		move_dir = HORIZONTAL;
		distance = ((newPos.x - oldPos.x) / pos_size);
	}
	else {
		return 0;
	}
	if (move_dir == VERTICAL) {
		if (distance > 0) {
			for (int i = 1; i < distance; i++) {
				for (int j = 0; j < 32; j++) {
					if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y - (i * pos_size))) {
						return 0;
					}
				}
			}
		}
		else if (distance < 0) {
			for (int i = -1; i > distance; i--) {
				for (int j = 0; j < 32; j++) {
					if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y - (i * pos_size))) {
						return 0;
					}
				}
			}
		}

		return 1;
	}
	else if (move_dir == HORIZONTAL) {
		if (distance > 0) {
			for (int i = 1; i < distance; i++) {
				for (int j = 0; j < 32; j++) {
					if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x + (i * pos_size), oldPos.y)) {
						return 0;
					}
				}
			}
		}
		else if (distance < 0) {
			for (int i = -1; i > distance; i--) {
				for (int j = 0; j < 32; j++) {
					if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x + (i * pos_size), oldPos.y)) {
						return 0;
					}
				}
			}
		}

		return 1;
	}
}
//Checks if given move as old position and new position is a "knight move or not"
inline static bool isKnightMove(sf::Vector2f oldPos, sf::Vector2f newPos) {
	if (abs(oldPos.x - newPos.x) == (int(pos_size) * 2) && abs(oldPos.y - newPos.y) == int(pos_size)) {
		return 1;
	}
	else if (abs(oldPos.y - newPos.y) == (int(pos_size) * 2) && abs(oldPos.x - newPos.x) == int(pos_size)) {
		return 1;
	}
	else {
		return 0;
	}
}
//Checks if given move as old position and new position is a "bishop move or not"
inline static bool isBishopMove(sf::Vector2f oldPos, sf::Vector2f newPos) {
	enum {
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};
	int move_dir = -1;
	int distance;

	if (!(abs(oldPos.x - newPos.x) == abs(oldPos.y - newPos.y))) {
		return 0;
	}
	distance = abs((oldPos.x - newPos.x) / pos_size);
	//direction
	if ((oldPos.y - newPos.y > 0) && (oldPos.x - newPos.x < 0)) {
		move_dir = TOP_RIGHT;
	}
	else if ((oldPos.y - newPos.y > 0) && (oldPos.x - newPos.x > 0)) {
		move_dir = TOP_LEFT;
	}
	else if ((oldPos.y - newPos.y < 0) && (oldPos.x - newPos.x < 0)) {
		move_dir = BOTTOM_RIGHT;
	}
	else if ((oldPos.y - newPos.y < 0) && (oldPos.x - newPos.x > 0)) {
		move_dir = BOTTOM_LEFT;
	}

	if (move_dir == TOP_LEFT) {
		for (int j = 0; j < 32; j++) {
			for (int i = 1; i < distance; i++) {
				if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x - (i * pos_size), oldPos.y - (i * pos_size))) {
					return 0;
				}
			}
		}
		return 1;
	}
	else if (move_dir == TOP_RIGHT) {
		for (int j = 0; j < 32; j++) {
			for (int i = 1; i < distance; i++) {
				if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x + (i * pos_size), oldPos.y - (i * pos_size))) {
					return 0;
				}
			}
		}
		return 1;
	}
	else if (move_dir == BOTTOM_LEFT) {
		for (int j = 0; j < 32; j++) {
			for (int i = 1; i < distance; i++) {
				if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x - (i * pos_size), oldPos.y + (i * pos_size))) {
					return 0;
				}
			}
		}
		return 1;
	}
	else if (move_dir == BOTTOM_RIGHT) {
		for (int j = 0; j < 32; j++) {
			for (int i = 1; i < distance; i++) {
				if (piece[j].sprite.getPosition() == sf::Vector2f(oldPos.x + (i * pos_size), oldPos.y + (i * pos_size))) {
					return 0;
				}
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}
//Checks if given move as old position and new position is a "king move or not"
inline static bool isKingMove(sf::Vector2f oldPos, sf::Vector2f newPos, bool White) {
	int index = getIndexFromPos(newPos);
	std::vector<int> occSq = getOccupiedSquares(!White);
	for (int i = 0; i < occSq.size(); i++) {
		if (occSq[i] == index) {
			return 0;
		}
	}
	if (newPos.x - oldPos.x == 0 && (abs(newPos.y - oldPos.y) == int(pos_size))) {
		return 1;
	}
	else if (newPos.y - oldPos.y == 0 && (abs(newPos.x - oldPos.x) == int(pos_size))) {
		return 1;
	}
	else if (abs(newPos.y - oldPos.y) == int(pos_size) && abs(newPos.x - oldPos.x) == int(pos_size)) {
		return 1;
	}
	else {
		return 0;
	}
}
//Checks if given move as old position and new position is a "pawn move or not"
inline static bool isPawnMove(sf::Vector2f oldPos, sf::Vector2f newPos, int indexMoved, int indexocc) {
	if (piece[indexMoved].isWhite) {
		if ((oldPos.y - newPos.y == int(pos_size)) && (oldPos.x == newPos.x)) {
			if (indexocc == -10) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (piece[indexMoved].isFirst && (oldPos.y - newPos.y == (int(pos_size) * 2)) && (oldPos.x == newPos.x)) {
			for (int i = 0; i < 32; i++) {
				if ((piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y - int(pos_size))) || (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y - int(pos_size * 2)))) {
					return 0;
				}
			}
			return 1;

		}
		else if ((abs(oldPos.x - newPos.x) == int(pos_size)) && (oldPos.y - newPos.y == int(pos_size))) {
			if (indexocc == -10) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(newPos.x, oldPos.y)) {
						if (piece[i].code != -PAWN) {

							return 0;
						}
						else {
							std::string  oldPsquare = chessSquare(sf::Vector2f(piece[i].sprite.getPosition().x, piece[i].sprite.getPosition().y - (int(pos_size) * 2)));
							if (chessSquare(piece[i].sprite.getPosition())[1] != '5' || (position.substr(position.length() - 10, 2) != oldPsquare)) {
								return 0;
							}
							else {
								return 1;
							}
						}
						return 1;
					}
				}
				return 0;
			}
			else {
				return 1;
			}
		}
		else {
			return 0;
		}
	}
	else if (!piece[indexMoved].isWhite) {
		if ((newPos.y - oldPos.y == int(pos_size)) && (oldPos.x == newPos.x)) {
			if (indexocc == -10) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (piece[indexMoved].isFirst == true && (newPos.y - oldPos.y == (int(pos_size) * 2)) && (oldPos.x == newPos.x)) {
			for (int i = 0; i < 32; i++) {
				if ((piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y + int(pos_size))) || (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x, oldPos.y + int(pos_size*2)))) {
					return 0;
				}
			}
			return 1;

		}
		else if ((abs(newPos.x - oldPos.x) == int(pos_size)) && (newPos.y - oldPos.y == int(pos_size))) { 
			if (indexocc == -10) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(newPos.x, oldPos.y)) {
						if (piece[i].code != PAWN) {

							return 0;
						}
						else {
							std::string oldPsquare = chessSquare(sf::Vector2f(piece[i].sprite.getPosition().x, piece[i].sprite.getPosition().y + (int(pos_size) * 2)));
							if (chessSquare(piece[i].sprite.getPosition())[1] != '4' || (position.substr(position.length() - 10, 2) != oldPsquare)) {
								return 0;
							}
							else {
								return 1;
							}
						}
						return 1;
					}
				}
				return 0;
			}
			else {
				return 1;
			}
		}
		else {
			return 0;
		}
	}
}

//Checks if given move as old position and new position is a "castle or not"
inline static bool isCastle(sf::Vector2f oldPos, sf::Vector2f newPos, int indexMoved, int indexocc) {
	enum {
		SCASTLE,
		LCASTLE
	};
	int castle_type = -1;
	if (abs(piece[indexMoved].code) != KING) {
		return 0;
	}
	if (indexocc != -10) {
		if (piece[indexMoved].isFirst && piece[indexocc].isFirst) {
			if (abs(piece[indexocc].code) != ROOK) {
				return 0;
			}
			if (newPos.x - oldPos.x == (int(pos_size) * 3) && (newPos.y == oldPos.y)) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x + int(pos_size), oldPos.y) || piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x + (int(pos_size) * 2), oldPos.y)) {
						return 0;
					}
				}
				castle_type = SCASTLE;
			}
			else if (oldPos.x - newPos.x == (int(pos_size) * 4) && (newPos.y == oldPos.y)) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - int(pos_size), oldPos.y) || piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - (int(pos_size) * 2), oldPos.y) || piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - (int(pos_size) * 3), oldPos.y)) {
						return 0;
					}
				}
				castle_type = LCASTLE;
			}
		}
		else {
			return 0;
		}
	}
	else {
		if (piece[indexMoved].isFirst) {
			Piece rook;
			if (newPos.x - oldPos.x == int(pos_size * 2) && (newPos.y == oldPos.y)) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x + int(pos_size), oldPos.y)) {
						return 0;
					}
				}
				for (int i = 0; i < 32; ++i) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(newPos.x + int(pos_size), newPos.y)) {
						rook = piece[i];
						break;
					}
					else if (i == 31) {
						return 0;
					}
				}
				if (rook.isFirst && (abs(rook.code) == ROOK)) {
					castle_type = SCASTLE;
				}
				else {
					return 0;
				}

			}
			else if (oldPos.x - newPos.x == int(pos_size * 2) && (newPos.y == oldPos.y)) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - int(pos_size), oldPos.y) || piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - int(pos_size * 3), oldPos.y)) {
						return 0;
					}
				}
				for (int i = 0; i < 32; ++i) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(newPos.x - int(pos_size * 2), newPos.y)) {
						rook = piece[i];
						break;
					}
					else if (i == 31) {
						return 0;
					}
				}
				if (rook.isFirst && (abs(rook.code) == ROOK)) {
					castle_type = LCASTLE;
				}
				else {
					return 0;
				}

			}
			else if (oldPos.x - newPos.x == int(pos_size * 3) && (newPos.y == oldPos.y)) {
				for (int i = 0; i < 32; i++) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - int(pos_size), oldPos.y) || piece[i].sprite.getPosition() == sf::Vector2f(oldPos.x - int(pos_size * 2), oldPos.y)) {
						return 0;
					}
				}
				for (int i = 0; i < 32; ++i) {
					if (piece[i].sprite.getPosition() == sf::Vector2f(newPos.x - int(pos_size), newPos.y)) {
						rook = piece[i];
						break;
					}
					else if (i == 31) {
						return 0;
					}
				}
				if (rook.isFirst && (abs(rook.code) == ROOK)) {
					castle_type = LCASTLE;
				}
				else {
					return 0;
				}

			}
		}
		else {
			return 0;
		}
	}
	if (castle_type != -1)return 1; 
	return 0;
}

//Checks if a given move as string is Valid or not
inline bool checkMove(std::string str) {
	sf::Vector2f oldPos = coord(str[0], str[1]);
	sf::Vector2f newPos = coord(str[2], str[3]);
	int movedPiece = NULL;
	int occupyingPiece = -10;
	bool isWhite = false;

	for (int i = 0; i < 32; i++) {
		if (piece[i].square.square == str.substr(0, 2)) {
			movedPiece = i;
			isWhite = piece[i].isWhite;
			break;
		}
	}
	for (int i = 0; i < 32; i++) {
		if (piece[i].square.square == str.substr(2, 2)) {
			occupyingPiece = i;
			break;
		}
	}
	//placed on same color
	for (int i = 0; i < 32; i++) {
		if ((piece[i].sprite.getPosition() == newPos)) {
			if (piece[i].isWhite == piece[movedPiece].isWhite) {
				if (!isCastle(oldPos, newPos, movedPiece, occupyingPiece)) {
					return 0;
				}
				else {
					if (isKingInCheck(isWhite)) return 0;
					return 1;
				}
			}
		}
	}
	//checking turn
	if (isWhite != isWhiteTurn) {
		return 0;
	}

	//checking move
	switch (abs(piece[movedPiece].code))
	{
	case ROOK:
		if (!isRookMove(oldPos, newPos))
			return 0;
		break;
	case KNIGHT:
		if (!isKnightMove(oldPos, newPos))
			return 0;
		break;
	case BISHOP:
		if (!isBishopMove(oldPos, newPos))
			return 0;
		break;
	case QUEEN:
		if (!isRookMove(oldPos, newPos) && !isBishopMove(oldPos,newPos))
			return 0;
		break;
	case KING:
		if (!isCastle(oldPos, newPos, movedPiece, occupyingPiece))
			if (!isKingMove(oldPos, newPos, isWhite))
				return 0;
		break;
	case PAWN:
		if (!isPawnMove(oldPos, newPos,movedPiece,occupyingPiece))
			return 0;
		break;
	default:
		break;
	}
	return 1;
}