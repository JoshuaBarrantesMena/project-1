#include "UnoEngine.h"
#include <string>

using namespace std;
using namespace sf;

RenderWindow game(VideoMode(1280, 720), "UNO!");
Texture backgroundFile, buttonFile, cardFile, cardOutlineFile;
Font letterFont;
Vector2i mousePos;
Event gameLoop;
UnoCard globalCard;

void startMenu() {
	while (game.isOpen()) {

		loopRefresh();

		backgroundFile.loadFromFile("Textures/Background.jpg");
		buttonFile.loadFromFile("Textures/Button.png");
		letterFont.loadFromFile("Fonts/Cabin-Bold.ttf");
		Sprite background(backgroundFile), button(buttonFile);

		Text menuText("¡JUEGA UNO EN C++!", letterFont, 90), buttonText("Empezar", letterFont, 60);

		button.setPosition(460, 280);
		menuText.setPosition(240, 70);
		buttonText.setPosition(530, 315);

		menuText.setColor(Color::Black);
		buttonText.setColor(Color::Black);

		game.setFramerateLimit(24);

		bool isInTop = false;
		bool isInBottom = false;
		bool isButtonPressed = false;

		while (isButtonPressed == false) {

			loopRefresh();

			game.draw(background);
			game.draw(menuText);
			game.draw(button);
			game.draw(buttonText);
			game.display();

			Vector2f top(460, 820), bottom(280, 440);

			if (mouseDetect(mousePos, top, bottom)) {
				buttonText.setColor(Color::White);
			}
			else {
				buttonText.setColor(Color::Black);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseDetect(mousePos, top, bottom)) {
				while (isButtonPressed == false) {
					if (Mouse::isButtonPressed(Mouse::Left) != true) {
						isButtonPressed = true;
					}
					loopRefresh();
				}
			}
		}
		game.draw(background);
		game.display();
		startGame();
		system("pause");
	}
}

void startGame() {

	CardsDeck gameDeck(108), playerOneDeck(12), playerTwoDeck(12);

	int bottomXPositions[12] = {556, 644, 468, 732, 380, 820, 292, 908, 204, 996, 116, 1084};
	int topXPositions[12] = {644, 556, 732, 468, 820, 380, 908, 292, 996, 204, 1084, 116};
	int iterCard, bottomYPosition = 570, topYPosition = 30;

	gameDeck.fillDeck();
	gameDeck.deckShufle();

	UnoCard auxCard;

	for (iterCard = 0; iterCard < 8; iterCard++) {

		auxCard = gameDeck.getCardDeck(iterCard);
		gameDeck.setCardInUse(iterCard, true);
		playerOneDeck.setCardDeck(auxCard, iterCard);

		auxCard = gameDeck.getCardDeck(iterCard + 8);
		gameDeck.setCardInUse(iterCard + 8, true);
		playerTwoDeck.setCardDeck(auxCard, iterCard);
	}

	gameDeck.print();
	playerOneDeck.print();
	playerTwoDeck.print();

	cardFile.loadFromFile("Textures/UnoCard.png");
	cardOutlineFile.loadFromFile("Textures/UnocardOutline.png");

	Sprite background(backgroundFile), button(buttonFile), card(cardFile), cardOutline(cardOutlineFile);
	Text unoText("UNO", letterFont, 60), takeCard("Tomar", letterFont, 27);
	
	unoText.setPosition(1090, 300);
	unoText.setColor(Color::Black);
	button.setScale(Vector2f(0.70, 0.70));
	button.setPosition(1028, 280);

	card.setScale(Vector2f(0.2, 0.2));
	cardOutline.setScale(Vector2f(0.2, 0.2));

	game.draw(background);
	game.draw(button);
	game.draw(unoText);

	card.setPosition(60, 300);

	game.draw(card);

	takeCard.setRotation(310);
	takeCard.setPosition(59, 380);
	takeCard.setColor(Color::Black);

	game.draw(takeCard);

	takeCard.setPosition(62, 379);
	takeCard.setColor(Color(255, 218, 0, 255));

	game.draw(takeCard);

	for (int i = 0; i < 12; i++) {
		printCard(playerOneDeck.getCardDeck(i), card, cardOutline, bottomXPositions[i], bottomYPosition);
	}

	for (int i = 0; i < 12; i++) {
		printCard(playerTwoDeck.getCardDeck(i), card, cardOutline, topXPositions[i], topYPosition);
	}

	game.display();

	bool isWaitingClick = true;

	while (true) {
		for (iterCard = 0; iterCard < playerOneDeck.getTotalCards(); iterCard++) {
			if (isClickingCard(bottomXPositions[iterCard], bottomYPosition)) {
				cout << iterCard + 1;
				isWaitingClick = false;
			}
		}

		for (iterCard = 0; iterCard < playerTwoDeck.getTotalCards(); iterCard++) {
			if (isClickingCard(topXPositions[iterCard], topYPosition)) {
				cout << iterCard + 1;
				isWaitingClick = false;
			}
		}

		loopRefresh();
	}
}

bool mouseDetect(Vector2i mousePos, Vector2f topPos, Vector2f bottomPos) {

	mousePos = Mouse::getPosition(game);

	bool isInTop = false;
	bool isInBottom = false;

	if ((mousePos.x > topPos.x) && (mousePos.x < topPos.y)) {
		isInTop = true;
	}
	else {
		isInTop = false;
	}

	if ((mousePos.y > bottomPos.x) && (mousePos.y < bottomPos.y)) {
		isInBottom = true;
	}
	else {
		isInBottom = false;
	}

	if (isInTop && isInBottom) {
		return true;
	}
	else {
		return false;
	}
}

void printCard(UnoCard actualCard, Sprite cardSprite, Sprite cardOutlineSprite, int xPos, int yPos) {

	string cardCharacter;
	int auxX = 0;

	switch (actualCard.getType()) {

	case 's':
		cardCharacter = "X";
		auxX = 6;
		break;
	case 'r':
		cardCharacter = "//";
		auxX = 3;
		break;
	case '2':
		cardCharacter = "+2";
		auxX = -7;
		break;
	case '4':
		cardCharacter = "+4";
		auxX = -8;
		break;
	case 'c':
		cardCharacter = "%";
		break;
	case 'n':
		cardCharacter = to_string(actualCard.getNumber());
		auxX = 7;
		if (cardCharacter == '1') {
			auxX += 5;
		}
		break;
	default:
		break;
	}

	Text cardText(cardCharacter, letterFont, 45);

	switch (actualCard.getColor()) {
	case 'B':
		cardText.setColor(Color::Blue);
		cardOutlineSprite.setColor(Color::Blue);
		break;
	case 'G':
		cardText.setColor(Color::Green);
		cardOutlineSprite.setColor(Color::Green);
		break;
	case 'R':
		cardText.setColor(Color::Red);
		cardOutlineSprite.setColor(Color::Red);
		break;
	case 'Y':
		cardText.setColor(Color::Yellow);
		cardOutlineSprite.setColor(Color::Yellow);
		break;
	case 'N':
		cardText.setColor(Color::Black);
		cardOutlineSprite.setColor(Color::Black);
		break;
	}
	cardSprite.setPosition(xPos, yPos);
	cardOutlineSprite.setPosition(xPos, yPos);

	if (actualCard.getType() != 'v'){
		game.draw(cardSprite);
		game.draw(cardOutlineSprite);
	}
	cardText.setPosition(xPos + 20 + auxX, yPos + 31);
	game.draw(cardText);
}

bool isClickingCard(int xPosCard, int yPosCard) {

	int minX = xPosCard;
	int maxX = xPosCard + (400 * 0.2);
	int minY = yPosCard;
	int maxY = minY + (600 * 0.2);

	Vector2f top(minX, maxX);
	Vector2f bottom(minY, maxY);

	bool isButtonPressed = false;

	if (Mouse::isButtonPressed(Mouse::Left) && (mouseDetect(mousePos, top, bottom))) {
		while (isButtonPressed == false) {
			if (Mouse::isButtonPressed(Mouse::Left) != true) {
				isButtonPressed = true;
			}
			loopRefresh();
		}
		return true;
	}
	return false;
}

void loopRefresh() {

	while (game.pollEvent(gameLoop)) {
		if (gameLoop.type == Event::Closed) {
			game.close();
		}
	}
}