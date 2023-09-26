#include "UnoEngine.h"
#include <string>

using namespace std;
using namespace sf;

RenderWindow game(VideoMode(1280, 720), "UNO!");
Texture backgroundFile, buttonFile, cardFile;
Texture cardOutlineFile, cardChangeColorFile, cardNoTurnFile, cardReverseFile, changeColorMenuFile;
Sprite background, button, buttonSkip, card, cardOutline, changeColorMenu;
Font letterFont;
Text unoText, takeCard, skip;
Vector2i mousePos;
Event gameLoop;
CardsDeck gameDeck(108), playerOneDeck(12), playerTwoDeck(12);
UnoCard globalCard, globalCardAux;
int jumpTurn;
int turn, winnerPlayer = 0;

void startMenu() {
	while (game.isOpen()) {

		loopRefresh();

		backgroundFile.loadFromFile("Textures/Background.jpg");
		buttonFile.loadFromFile("Textures/Button.png");
		letterFont.loadFromFile("Fonts/Cabin-Bold.ttf");
		cardChangeColorFile.loadFromFile("Textures/UnocardChangeColor.png");
		cardNoTurnFile.loadFromFile("Textures/UnocardNoTurn.png");
		cardReverseFile.loadFromFile("Textures/UnocardReverse.png");
		cardFile.loadFromFile("Textures/UnoCard.png");
		cardOutlineFile.loadFromFile("Textures/UnocardOutline.png");
		changeColorMenuFile.loadFromFile("Textures/ChangeColorMenu.png");

		background.setTexture(backgroundFile);
		button.setTexture(buttonFile);
		buttonSkip.setTexture(buttonFile);
		card.setTexture(cardFile);
		cardOutline.setTexture(cardOutlineFile);
		changeColorMenu.setTexture(changeColorMenuFile);

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

		startGame();
	}
}

void startGame() {

	int bottomXPositions[12] = { 556, 644, 468, 732, 380, 820, 292, 908, 204, 996, 116, 1084 };
	int topXPositions[12] = { 644, 556, 732, 468, 820, 380, 908, 292, 996, 204, 1084, 116 };
	int bottomYPosition = 570, topYPosition = 30;
	turn = 1;

	Text winnerText(" ", letterFont, 50);
	winnerText.setPosition(600, 335);
	winnerText.setColor(Color::Magenta);

	gameDeck.fillDeck();
	gameDeck.deckShufle();

	UnoCard auxCard;
	int iterCard;

	for (iterCard = 0; iterCard < 8; iterCard++) {

		auxCard = gameDeck.getCardDeck(iterCard);
		playerOneDeck.setCardDeck(auxCard, iterCard);
		gameDeck.setCardDeck(*new UnoCard, iterCard);

		auxCard = gameDeck.getCardDeck(iterCard + 8);
		playerTwoDeck.setCardDeck(auxCard, iterCard);
		gameDeck.setCardDeck(*new UnoCard, iterCard + 8);
	}

	globalCard = gameDeck.getCardDeck(16);
	globalCardAux = globalCard;
	gameDeck.organizeDeck();

	unoText.setString("UNO");
	unoText.setFont(letterFont);
	unoText.setCharacterSize(60);

	skip.setString("saltar");
	skip.setFont(letterFont);
	skip.setCharacterSize(30);
	skip.setColor(Color::Black);
	skip.setPosition(65, 200);

	takeCard.setString("Tomar");
	takeCard.setFont(letterFont);
	takeCard.setCharacterSize(27);

	unoText.setPosition(1090, 300);
	unoText.setColor(Color::Black);

	card.setScale(Vector2f(0.2, 0.2));
	cardOutline.setScale(Vector2f(0.2, 0.2));
	button.setScale(Vector2f(0.70, 0.70));
	buttonSkip.setScale(Vector2f(0.4, 0.4));

	button.setPosition(1028, 280);
	buttonSkip.setPosition(30, 190);

	changeColorMenu.setScale(Vector2f(0.2, 0.2));
	changeColorMenu.setPosition(385, 240);

	bool isWaitingClick = true;
	int selectedCard = -1;

	bool isUsableCardOne[12];
	bool isUsableCardTwo[12];
	bool continueGame = true;

	jumpTurn = 0;

	while (continueGame) {

		while (isWaitingClick) {

			for (iterCard = 0; iterCard < playerOneDeck.getSize(); iterCard++) {
				if (verifyCard(playerOneDeck.getCardDeck(iterCard))) {
					isUsableCardOne[iterCard] = true;
				}
				else {
					isUsableCardOne[iterCard] = false;
				}
			}
			for (iterCard = 0; iterCard < playerOneDeck.getTotalCards(); iterCard++) {
				if (isClickingCard(bottomXPositions[iterCard], bottomYPosition) && isUsableCardOne[iterCard] && jumpTurn == 0) {
					actionCard(playerOneDeck.getCardDeck(iterCard), iterCard, true);
					isWaitingClick = false;
				}
			}
			if (skipTurn()) {
				isWaitingClick = false;
			}

			takeActionCard(true);
			if (jumpTurn != 0) {
				isWaitingClick = false;
			}
			refreshWindow(bottomXPositions, topXPositions, bottomYPosition, topYPosition);
			loopRefresh();
		}
		turn++;
		isWaitingClick = true;
		if (jumpTurn != 0) {
			jumpTurn--;
		}

		if (playerOneDeck.getTotalCards() == 0) {
			continueGame = false;
			winnerPlayer = 1;
			break;
		}

		while (isWaitingClick) {

			for (iterCard = 0; iterCard < playerTwoDeck.getSize(); iterCard++) {
				if (verifyCard(playerTwoDeck.getCardDeck(iterCard))) {
					isUsableCardTwo[iterCard] = true;
				}
				else {
					isUsableCardTwo[iterCard] = false;
				}
			}
			for (iterCard = 0; iterCard < playerTwoDeck.getTotalCards(); iterCard++) {
				if (isClickingCard(topXPositions[iterCard], topYPosition) && isUsableCardTwo[iterCard] && jumpTurn == 0) {
					actionCard(playerTwoDeck.getCardDeck(iterCard), iterCard, false);
					isWaitingClick = false;
				}
			}
			if (skipTurn()) {
				isWaitingClick = false;
			}

			takeActionCard(false);
			if (jumpTurn != 0) {
				isWaitingClick = false;
			}

			refreshWindow(bottomXPositions, topXPositions, bottomYPosition, topYPosition);
			loopRefresh();
		}
		turn++;
		isWaitingClick = true;
		if (jumpTurn != 0) {
			jumpTurn--;
		}

		if (playerTwoDeck.getTotalCards() == 0) {
			continueGame = false;
			winnerPlayer = 2;
			break;
		}

		loopRefresh();
	}
	if (winnerPlayer == 1) {
		winnerText.setString("Gano el Jugador #1");
	}
	else {
		winnerText.setString("Gano el Jugador #1");
	}

	while (game.isOpen()) {
		game.draw(winnerText);
		game.display();
		loopRefresh();
	}
}

void printCard(UnoCard pActualCard, int pXPos, int pYPos) {

	string cardCharacter = " ";
	Sprite changeColor(cardChangeColorFile), noTurn(cardNoTurnFile), reverse(cardReverseFile);
	int auxX = 0;
	bool isChangeColor = false;
	bool isReverse = false;
	bool isNoTurn = false;

	switch (pActualCard.getType()) {

	case 's':
		isNoTurn = true;
		break;
	case 'r':
		isReverse = true;
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
		isChangeColor = true;
		break;
	case 'n':
		cardCharacter = to_string(pActualCard.getNumber());
		auxX = 7;
		if (cardCharacter == '1') {
			auxX += 5;
		}
		break;
	default:
		break;
	}

	Text cardText(cardCharacter, letterFont, 45);

	switch (pActualCard.getColor()) {
	case 'B':
		cardText.setColor(Color::Blue);
		cardOutline.setColor(Color::Blue);
		reverse.setColor(Color::Blue);
		noTurn.setColor(Color::Blue);
		break;
	case 'G':
		cardText.setColor(Color::Green);
		cardOutline.setColor(Color::Green);
		reverse.setColor(Color::Green);
		noTurn.setColor(Color::Green);
		break;
	case 'R':
		cardText.setColor(Color::Red);
		cardOutline.setColor(Color::Red);
		reverse.setColor(Color::Red);
		noTurn.setColor(Color::Red);
		break;
	case 'Y':
		cardText.setColor(Color::Yellow);
		cardOutline.setColor(Color::Yellow);
		reverse.setColor(Color::Yellow);
		noTurn.setColor(Color::Yellow);
		break;
	case 'N':
		cardText.setColor(Color::Black);
		cardOutline.setColor(Color::Black);
		break;
	}
	card.setPosition(pXPos, pYPos);
	cardOutline.setPosition(pXPos, pYPos);

	if (pActualCard.getType() != 'v') {
		game.draw(card);
		game.draw(cardOutline);
	}
	if (isChangeColor) {
		changeColor.setPosition(pXPos, pYPos);
		changeColor.setScale(Vector2f(0.2, 0.2));
		game.draw(changeColor);
	}
	if (isReverse) {
		reverse.setPosition(pXPos, pYPos);
		reverse.setScale(Vector2f(0.2, 0.2));
		game.draw(reverse);
	}
	if (isNoTurn) {
		noTurn.setPosition(pXPos, pYPos);
		noTurn.setScale(Vector2f(0.2, 0.2));
		game.draw(noTurn);
	}

	cardText.setPosition(pXPos + 20 + auxX, pYPos + 31);
	game.draw(cardText);
}

void refreshWindow(int* pBottomXPositions, int* pTopXPositions, int pBottomYPosition, int pTopYPosition) {

	int iterCard;

	game.draw(background);
	game.draw(unoText);

	game.draw(button);
	game.draw(unoText);
	game.draw(buttonSkip);
	game.draw(skip);

	card.setPosition(60, 300);
	game.draw(card);

	takeCard.setRotation(310);
	takeCard.setPosition(59, 380);
	takeCard.setColor(Color::Black);
	game.draw(takeCard);
	takeCard.setPosition(62, 379);
	takeCard.setColor(Color(255, 218, 0, 255));
	game.draw(takeCard);

	for (iterCard = 0; iterCard < 12; iterCard++) {
		printCard(playerOneDeck.getCardDeck(iterCard), pBottomXPositions[iterCard], pBottomYPosition);
	}
	for (iterCard = 0; iterCard < 12; iterCard++) {
		printCard(playerTwoDeck.getCardDeck(iterCard), pTopXPositions[iterCard], pTopYPosition);
	}
	printCard(globalCardAux, 600, 300);

	game.display();
}

void addCardAction(int pNumOfCards, bool pIsPlayerOneDeck){

	int iterCard;

	if (pIsPlayerOneDeck) {
		if (playerOneDeck.getTotalCards() < playerOneDeck.getSize()) {
			for (iterCard = 0; iterCard < pNumOfCards; iterCard++) {

				playerOneDeck.addOrganizeCard(gameDeck.getCardDeck(0), true);
				gameDeck.setCardDeck(*new UnoCard, 0);
				gameDeck.organizeDeck();
			}
		}
	}
	else {
		if (playerTwoDeck.getTotalCards() < playerTwoDeck.getSize()) {
			for (iterCard = 0; iterCard < pNumOfCards; iterCard++) {

				playerTwoDeck.addOrganizeCard(gameDeck.getCardDeck(0), true);
				gameDeck.setCardDeck(*new UnoCard, 0);
				gameDeck.organizeDeck();
			}
		}
	}
}

void actionCard(UnoCard pActualCard, int pPositionCard, bool pIsPlayerOneDeck){

	gameDeck.addOrganizeCard(globalCard, true);
	globalCard = pActualCard;
	globalCardAux = globalCard;

	if (pIsPlayerOneDeck) {
		playerOneDeck.setCardDeck(*new UnoCard, pPositionCard);
		playerOneDeck.organizeDeck();
	}
	else {
		playerTwoDeck.setCardDeck(*new UnoCard, pPositionCard);
		playerTwoDeck.organizeDeck();
	}

	switch (pActualCard.getType()) {

	case 's':

		jumpTurn = 2;
		break;

	case 'r':
		jumpTurn = 2;
		break;
	case '2':

		if (pIsPlayerOneDeck) {
			pIsPlayerOneDeck = false;
		}
		else {
			pIsPlayerOneDeck = true;
		}
		addCardAction(2, pIsPlayerOneDeck);
		break;

	case '4':

		changeColorAction();
		if (pIsPlayerOneDeck) {
			pIsPlayerOneDeck = false;
		}
		else {
			pIsPlayerOneDeck = true;
		}
		addCardAction(4, pIsPlayerOneDeck);
		break;

	case 'c':

		changeColorAction();
		break;

	case 'n':

		if (pActualCard.getNumber() == 0) {
			UnoCard auxCard;
			int iterCard, auxIterCard = playerOneDeck.getSize();
			for (int iterCard = 0; iterCard < playerOneDeck.getSize(); iterCard++) {
				auxCard = playerOneDeck.getCardDeck(iterCard);
				playerOneDeck.setCardDeck(playerTwoDeck.getCardDeck(iterCard), iterCard);
				playerTwoDeck.setCardDeck(auxCard, iterCard);
			}
		}
		break;

	default:
		break;
	}
}

void takeActionCard(bool pIsPlayerOneDeck) {

	if (isClickingCard(60, 300)) {
		addCardAction(1, pIsPlayerOneDeck);
	}
}

void changeColorAction() {

	const int colorNumber = 4;
	int iterCard, colorAux;
	bool isClickingColor = true;

	char colors[colorNumber] = { 'Y', 'G', 'B', 'R' };

	int changeColorXCoord[colorNumber] = {385, 465, 385, 465};
	int changeColorYCoord[colorNumber] = {240, 240, 360, 360};

	game.draw(changeColorMenu);
	game.display();

	while (isClickingColor) {
		for (iterCard = 0; iterCard < colorNumber; iterCard++) {
			if (isClickingCard(changeColorXCoord[iterCard], changeColorYCoord[iterCard])) {
				colorAux = iterCard;
				isClickingColor = false;
			}
		}
		loopRefresh();
	}
	globalCardAux.setColor(colors[colorAux]);
}

void loopRefresh() {

	while (game.pollEvent(gameLoop)) {
		if (gameLoop.type == Event::Closed) {
			game.close();
		}
	}
}

bool mouseDetect(Vector2i pMousePosition, Vector2f pTopPosition, Vector2f pBottomPosition) {

	mousePos = Mouse::getPosition(game);

	bool isInTop = false;
	bool isInBottom = false;

	if ((pMousePosition.x > pTopPosition.x) && (pMousePosition.x < pTopPosition.y)) {
		isInTop = true;
	}
	else {
		isInTop = false;
	}

	if ((pMousePosition.y > pBottomPosition.x) && (pMousePosition.y < pBottomPosition.y)) {
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

bool isClickingCard(int pXPositionCard, int pYPositionCard) {

	int minX = pXPositionCard;
	int maxX = pXPositionCard + (400 * 0.2);
	int minY = pYPositionCard;
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


bool verifyCard(UnoCard pSelectedCard) {

	if (pSelectedCard.getType() == 'v') {
		return false;
	}

	switch (pSelectedCard.getType()) {

	case 's':
		if ((turn == 1 && globalCardAux.getColor() == pSelectedCard.getColor()) ||
			(globalCardAux.getColor() == pSelectedCard.getColor() && globalCardAux.getType() != 'r' &&
				globalCardAux.getType() != '4')) {
			return true;
		}
		break;
	case 'r':
		if ((turn == 1 && globalCardAux.getColor() == pSelectedCard.getColor()) || (globalCardAux.getType() != '4' &&
			globalCardAux.getColor() == pSelectedCard.getColor()) &&
			globalCardAux.getType() != 'r') {
			return true;
		}
		break;
	case '2':
		if ((turn == 1 && globalCardAux.getColor() == pSelectedCard.getColor()) ||
			(globalCardAux.getType() != 'r' && globalCardAux.getType() != '2') &&
			globalCardAux.getColor() == pSelectedCard.getColor()) {
			return true;
		}
		break;
	case '4':
		if (globalCardAux.getType() != 'r') {
			return true;
		}
		break;
	case 'c':
		if (turn == 1 || globalCardAux.getType() != 'r') {
			return true;
		}
		break;
	case 'n':
		if ((pSelectedCard.getColor() == globalCardAux.getColor() && globalCardAux.getType() != 'v') ||
			(turn == 1 && pSelectedCard.getColor() == globalCardAux.getColor())) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool skipTurn() {

	bool isButtonPressed = false;

	Vector2f top(30, 190), bottom(174, 254);

	if (Mouse::isButtonPressed(Mouse::Left) && mouseDetect(mousePos, top, bottom)) {
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