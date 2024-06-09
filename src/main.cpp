
#include "Utility.cpp"
#include "functions.cpp"
#include "Moves.cpp"

int main() {
	bool debug = false;
	sf::Font Venite;
	Venite.loadFromFile("Assets/font.ttf");
	sf::RectangleShape rect;
	sf::Text m_pos_text;
	sf::Text Piece_text;
	sf::FloatRect play_game;
	sf::Text menu_text;
	sf::Text m_square_text;
	sf::Text turn;
	sf::Text score_text;
	sf::Text square_index_text;
	sf::Text fps_text;
	sf::Clock clock;
	sf::Time delta_time;
	sf::RectangleShape rectOverlay;
	float xOffset = 0;

	{
		rect.setFillColor(sf::Color::Red);
		sf::Color color = rect.getFillColor();
		color.a = 80;
		rect.setFillColor(color);
		rect.setPosition(100, 100);
		rect.setSize(sf::Vector2f(86, 86));

		m_pos_text.setFont(Venite);
		m_pos_text.setCharacterSize(24);
		m_pos_text.setFillColor(sf::Color::Red);
		m_pos_text.setOutlineThickness(5);
		m_pos_text.setPosition(0, 0);
		m_pos_text.setStyle(sf::Text::Bold);

		menu_text.setFont(Venite);
		menu_text.setCharacterSize(24);
		menu_text.setFillColor(sf::Color::White);
		menu_text.setOutlineThickness(2);
		menu_text.setPosition(324, 100);

		Piece_text.setFont(Venite);
		Piece_text.setCharacterSize(24);
		Piece_text.setFillColor(sf::Color::Red);
		Piece_text.setOutlineThickness(5);
		Piece_text.setPosition(0, 200);
		Piece_text.setStyle(sf::Text::Bold);

		m_square_text.setFont(Venite);
		m_square_text.setCharacterSize(24);
		m_square_text.setFillColor(sf::Color::Red);
		m_square_text.setOutlineThickness(5);
		m_square_text.setPosition(0, 100);
		m_square_text.setStyle(sf::Text::Bold);

		turn.setFont(Venite);
		turn.setCharacterSize(20);
		turn.setOutlineThickness(5);
		turn.setPosition(267, 0);
		turn.setStyle(sf::Text::Bold);

		score_text.setFont(Venite);
		score_text.setCharacterSize(20);
		score_text.setOutlineThickness(5);
		score_text.setStyle(sf::Text::Bold);
		score_text.setPosition(580, 0);

		square_index_text.setFont(Venite);
		square_index_text.setCharacterSize(24);
		square_index_text.setFillColor(sf::Color::Red);
		square_index_text.setOutlineThickness(5);
		square_index_text.setPosition(0, 150);
		square_index_text.setStyle(sf::Text::Bold);

		fps_text.setFont(Venite);
		fps_text.setCharacterSize(24);
		fps_text.setFillColor(sf::Color::Red);
		fps_text.setOutlineThickness(5);
		fps_text.setPosition(0, 50);
		fps_text.setStyle(sf::Text::Bold);


		rectOverlay.setFillColor(sf::Color::Black);
		rectOverlay.setSize(sf::Vector2f(720, 720));
		rectOverlay.setFillColor(sf::Color::Black);
		color = rectOverlay.getFillColor();
		color.a = 110;
		rectOverlay.setFillColor(color);
		rectOverlay.setPosition(0, 0);

	}

	window.setFramerateLimit(100);

	sf::Vector2i window_pos = sf::Vector2i(325, -10);
	window.setPosition(window_pos);
	sf::Image icon;

	icon.loadFromFile("Assets/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	sf::Texture t1, t2, menu;
	t2.loadFromFile("Assets/ChessBoard.png");
	t1.loadFromFile("Assets/figures.png");
	menu.loadFromFile("Assets/menu.jpg");
	sf::Sprite s(t1);
	sf::Sprite sboard(t2);
	sf::Sprite sMenu(menu);

	float zoomlevel = 1.0f;
	bool windowMaximized = false;
	sboard.setScale(0.53f, 0.53f);
	sMenu.setScale(3.93f, 3.93f);

	for (int i = 0; i < 32; i++) {
		piece[i].sprite.setTexture(t1);
	}
	initGame();
	loadPosition();
	float dx = 0, dy = 0;
	sf::Vector2f newPos, oldPos;
	std::string str;
	std::vector<Square> legalsq;
	while (window.isOpen()) {
		delta_time = clock.restart();
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			}break;
			case sf::Event::MouseButtonPressed: {
				if (event.key.code == sf::Mouse::Left) {
					if (!gameover) {
						if (gamemode == GM_GAMEPLAY) {
							for (int i = 0; i < 32; i++) {
								if (piece[i].sprite.getGlobalBounds().contains(float(pos.x - xOffset), float(pos.y))) {
									selected = i;
									if (!isMove && (piece[i].isWhite == isWhiteTurn)) {
										legalsq = getLegalSquares(piece[selected]);
									}
									isMove = true;
									dx = pos.x - piece[i].sprite.getPosition().x;
									dy = pos.y - piece[i].sprite.getPosition().y;
									oldPos = piece[i].sprite.getPosition();
								}
							}
						}
					}
					leftClicked = true;
				}

			}break;
			case sf::Event::MouseButtonReleased: {
				if (event.key.code == sf::Mouse::Left) {
					if (!gameover) {
						if (isMove) {
							sf::Vector2f p = piece[selected].sprite.getPosition() + sf::Vector2f(pos_size / 2, pos_size / 2) - additional;
							newPos = sf::Vector2f(pos_size * int(p.x / pos_size), pos_size * int(p.y / pos_size)) + additional;
							bool isWrongMove = false;
							if (oldPos != newPos && piece[selected].isWhite == isWhiteTurn) {
								str = chessSquare(oldPos) + chessSquare(newPos);
								position += str + " ";
								board_changed = true;
								if (isSquareOccupied(newPos)) {
									isCapture = true;
								}
								if (!checkMove(str)) {
									std::cout << "[!] Wrong Move : " << str << "\n";
									isWrongMove = true;
									board_changed = false;
									isCapture = false;
									back();
								}
								//Change Turn
								isWhiteTurn = !isWhiteTurn;
							}
							loadPosition();
							isMove = false;
							if (!isWrongMove && isKingInCheck(!isWhiteTurn)) {
								std::cout << "[!] Your King is in check after this move : " << str << "\n";
								board_changed = false;
								isCapture = false;
								back();
								loadPosition();
							}
							int start = 16, end = 32;
							if (!isWhiteTurn) {
								start = 0;
								end = 16;
							}
							std::vector<Square> squares = {};
							for (int i = start; i < end; i++) {
								std::vector<Square> csq = getLegalSquares(piece[i]);
								for (Square ssq : csq) {
									squares.push_back(ssq);
								}

								if (squares.size())
									break;

								if (i == end - 1) {
									if (isWhiteTurn)
										gameover = 1;
									else
										gameover = 2;
								}
							}
						}
					}
					leftClicked = false;
				}
			}break;
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::R) {
					position.erase(0, position.length());
					loadPosition();
					isWhiteTurn = true;
					window.setSize(sf::Vector2u(720, 720));
					window.setPosition(window_pos);
					board_changed = true;
				}
				else if (event.key.code == sf::Keyboard::BackSpace) {
					back();
					halfmovec -= 1;
					board_changed = true;
				}
				else if (event.key.code == sf::Keyboard::E) {
					window.setSize(sf::Vector2u(720, 720));
					window.setPosition(window_pos);
				}
				else if (event.key.code == sf::Keyboard::A) {
					isLogOn = !isLogOn;
				}
				else if (event.key.code == sf::Keyboard::Space) {
					std::string fen = fenPosition();
					std::cout << fen<<"\n";
					std::cout << position << "\n";
				}
			}break;
			case sf::Event::Resized: {
				float newWidth = static_cast<float>(event.size.width);
				float newHeight = 720.f;
				sf::View view(sf::FloatRect(0, 0, newWidth, newHeight));
				xOffset = (newWidth - window.getSize().y) / 2.0f;
				float yOffset = 0;
				view.move(-xOffset, -yOffset);
				window.setView(view);
			}break;
			}
		}
		//game code
		if (isMove) {
			piece[selected].sprite.setPosition(pos.x - dx, pos.y - dy);
		}


		if(board_changed)
		{
			if (!isWhiteTurn) {
				fullmovec++;
			}
			en_passant = "null";
			halfmovec++;
			//en passant check
			std::vector<Square> squares = {};
			for (int i = 0; i < 8; i++) {
				int index = isWhiteTurn ? i + 16 : i + 8;
				if (chessSquare(piece[index].sprite.getPosition())[1] != (piece[index].isWhite ? '5' : '4'))continue;
				squares = getLegalSquares(piece[index]);
				if (squares.size()) {
					sf::Vector2f oldPos = piece[index].sprite.getPosition();
					sf::Vector2f newPos = {};
					for (auto square : squares) {
						newPos = coord(square.square[0],square.square[1]);
						if (!isSquareOccupied(newPos) && abs(newPos.x - oldPos.x) == pos_size && abs(newPos.y - oldPos.y) == pos_size) {
							en_passant = square.square;
						}

					}
				}
			}
			//halfmove check
			if (abs(piece[selected].code) == PAWN || isCapture) {
				halfmovec = 0;
			}


			board_changed = false;
			isCapture = false;
		}
		//text
		if (isWhiteTurn) {
			turn.setOutlineColor(sf::Color::Black);
			turn.setFillColor(sf::Color::White);
			turn.setString("White's Turn");
		}
		else {
			turn.setOutlineColor(sf::Color::White);
			turn.setFillColor(sf::Color::Black);
			turn.setString("Black's Turn");
		}
		score_text.setString("Score: " + std::to_string(score));
		if (score > 0) {
			score_text.setFillColor(sf::Color::White);
			score_text.setOutlineColor(sf::Color::Black);
		}
		else if (score < 0) {
			score_text.setFillColor(sf::Color::Black);
			score_text.setOutlineColor(sf::Color::White);
		}
		int fps = int(1.0f / delta_time.asSeconds());

		//Render
		window.clear();
		if (gamemode == GM_GAMEPLAY)
		{
			window.draw(sboard);
			if (isMove && (piece[selected].isWhite == isWhiteTurn)) {
				for (Square sq : legalsq) {
					int sq_column = getColumnFromIndex(getIndexFromPos(sq.pos)) - 1;
					int sq_row = getRowFromIndex(getIndexFromPos(sq.pos)) - 1;
					float distance = 86.f;
					float distance_y = 85.8f;
					rect.setPosition(((additional.x - 8) + (distance * sq_column)), (additional.y + (distance_y * sq_row)));
					window.draw(rect);
				}
			}
			for (int i = 0; i < 32; i++) {
				if (isMove && i == selected) continue;
				window.draw(piece[i].sprite);
			}
			if (debug) {
				std::string mouse_pos = "Mouse:" + std::to_string(pos.x) + " " + std::to_string(pos.y);
				fps_text.setString("FPS:" + std::to_string(fps));
				m_pos_text.setString(mouse_pos);
				m_square_text.setString(chessSquare(sf::Vector2f(pos.x, (pos.y - int(pos_size)))));
				if (isMove) {
					Piece_text.setString("Piece:" + std::to_string(selected));
					window.draw(Piece_text);

				}
				int square_y = int((pos.y - additional.y) / pos_size);
				int square_x = int((pos.x - additional.x) / pos_size);
				int number = square_y * 8 + square_x;
				square_index_text.setString(std::to_string(number));
				window.draw(square_index_text);
				window.draw(m_pos_text);
				window.draw(m_square_text);
				window.draw(fps_text);
			}
			window.draw(turn);
			window.draw(score_text);
			if (isMove) {
				piece[selected].sprite.setScale(1.2f, 1.2f);
				window.draw(piece[selected].sprite);
			}
			if (gameover) {
				if (gameover != 3) {
					std::string winner = gameover == 1 ? "Black Won!" : "White Won!";
					window.draw(rectOverlay);
					menu_text.setFillColor(sf::Color::White);
					menu_text.setPosition(170, 100);
					menu_text.setString(winner);
					menu_text.setCharacterSize(60);
					sf::Color wincolor(200, 200, 150);
					menu_text.setFillColor(wincolor);
					window.draw(menu_text);

					menu_text.setCharacterSize(40);
					menu_text.setFillColor(sf::Color::White);
					menu_text.setPosition(250, 250);
					menu_text.setString("New Game");
					menu_text.setFillColor(sf::Color::White);
					if (menu_text.getGlobalBounds().contains(pos.x, pos.y)) {
						menu_text.setFillColor(sf::Color::Red);
						if (leftClicked) {
							resetGame();
							gameover = 0;
						}
					}
					window.draw(menu_text);

					menu_text.setFillColor(sf::Color::White);
					menu_text.setString("back");
					menu_text.setPosition(300,350);
					if (menu_text.getGlobalBounds().contains(pos.x, pos.y)) {
						menu_text.setFillColor(sf::Color::Red);
						if (leftClicked) {
							gameover = 0;
							back();
						}
					}
					window.draw(menu_text);

					menu_text.setCharacterSize(40);
					menu_text.setFillColor(sf::Color::White);
					menu_text.setPosition(302, 450);
					menu_text.setString("Menu");
					menu_text.setFillColor(sf::Color::White);
					if (menu_text.getGlobalBounds().contains(pos.x, pos.y)) {
						menu_text.setFillColor(sf::Color::Red);
						if (leftClicked) {
							resetGame();
							gameover = 0;
							gamemode = GM_MENU;
						}
					}
					window.draw(menu_text);
				}
			}
		}
		else if (gamemode == GM_MENU) {
			window.draw(sMenu);
			menu_text.setFillColor(sf::Color::White);
			menu_text.setPosition(155, 100);
			menu_text.setCharacterSize(100);
			menu_text.setString("Chess!");
			window.draw(menu_text);
			menu_text.setString("Play game");
			menu_text.setCharacterSize(40);
			menu_text.setPosition(240, 300);
			play_game = menu_text.getGlobalBounds();
			if (play_game.contains(sf::Vector2f(pos.x - xOffset, pos.y))) {
				menu_text.setFillColor(sf::Color::Red);
				if(leftClicked)
					gamemode = GM_GAMEPLAY;
			}
			window.draw(menu_text);
		} 
		//Display
		window.display();

	}
	return 0;
}