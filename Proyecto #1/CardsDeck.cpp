#include "CardsDeck.h"

CardsDeck::CardsDeck() {

	size = 108;
	int iter;
	deck = new UnoCard[size];

	for (iter = 0; iter < size; iter++) {

		deck[iter] = *new UnoCard;
	}
}

CardsDeck::CardsDeck(int pDeckSize) {

	size = pDeckSize;
	int iter;
	deck = new UnoCard[size];

	for (iter = 0; iter < size; iter++) {

		deck[iter] = *new UnoCard;
	}
}

CardsDeck::~CardsDeck() {

}

void CardsDeck::fillDeck() {

	const int numberCards = 10, comodinColorCards = 3, colorCards = 4;
	const char colors[5] = { 'B', 'G', 'R', 'Y' , 'N' };
	const char cardType[6] = {'s', 'r', '2', '4', 'c', 'n'};

	int iterCard, iterColor, iterTypePos, arrayControl = 0;

	for (iterColor = 0; iterColor < colorCards; iterColor++) {
		for (iterCard = 0; iterCard < numberCards; iterCard++) {

			if (iterCard != 0) {

				deck[arrayControl] = UnoCard(iterCard, colors[iterColor], cardType[5]);
				arrayControl++;
				deck[arrayControl] = UnoCard(iterCard, colors[iterColor], cardType[5]);
				arrayControl++;
			}
			else {
				deck[arrayControl] = UnoCard(iterCard, colors[iterColor], cardType[5]);
				arrayControl++;
			}
		}
	}

	for (iterCard = 0; iterCard < comodinColorCards; iterCard++) {
		for (iterColor = 0; iterColor < colorCards; iterColor++) {

			deck[arrayControl] = UnoCard(-1, colors[iterColor], cardType[iterCard]);
			arrayControl++;
			deck[arrayControl] = UnoCard(-1, colors[iterColor], cardType[iterCard]);
			arrayControl++;
		}
	}

	for (iterCard = 1; iterCard < comodinColorCards; iterCard++) {
		for (iterTypePos = 0; iterTypePos < colorCards; iterTypePos++) {

			deck[arrayControl] = UnoCard(-1, colors[4], cardType[iterCard + 2]);
			arrayControl++;
		}
	}
}

void CardsDeck::deckShufle() {

	UnoCard saveCard;
	int iter, randomPos;

	for (iter = 0; iter < size; iter++) {

		saveCard = deck[iter];
		randomPos = rand() % (size);
		deck[iter] = deck[randomPos];
		deck[randomPos] = saveCard;
	}
}

void CardsDeck::setCardDeck(UnoCard pActualCard, int pCardPosition) {

	deck[pCardPosition] = pActualCard;
}

void CardsDeck::organizeDeck() {

	int iter, aux;
	UnoCard auxCard;

	for (iter = 0; iter < size; iter++) {

		aux = iter;
		auxCard = deck[iter];

		while (aux > 0 && deck[aux - 1].getType() == 'v') {
			deck[aux] = deck[aux - 1];
			aux--;
		}
		deck[aux] = auxCard;
	}
}

void CardsDeck::addOrganizeCard(UnoCard pCard, bool pStackDeck) {

	int iter = 0;
	UnoCard auxCard;

	if (pStackDeck) {
		while (deck[iter].getType() != 'v') {
			iter++;
		}
		deck[iter] = pCard;
	}
	else {
		for (iter = size - 1; iter > 0; iter--) {
			deck[iter] = deck[iter - 1];
		}
		deck[0] = pCard;
	}
}

int CardsDeck::getTotalCards() {

	int iterDeck, totalCards = 0;

	for (iterDeck = 0; iterDeck < size; iterDeck++) {

		if (deck[iterDeck].getType() != 'v') {
			totalCards++;
		}
	}
	return totalCards;
}

int CardsDeck::getSize() {

	return size;
}

UnoCard CardsDeck::getCardDeck(int pCardPosition) {

	return deck[pCardPosition];
}