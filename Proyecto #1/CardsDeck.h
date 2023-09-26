#pragma once
#include "UnoCard.h"

class CardsDeck {

private:

	int size;
	UnoCard* deck;

public:
	CardsDeck();
	CardsDeck(int);
	~CardsDeck();

	void fillDeck();
	void deckShufle();
	void setCardDeck(UnoCard, int);
	void organizeDeck();
	void addOrganizeCard(UnoCard, bool);

	int getTotalCards();
	int getSize();

	UnoCard getCardDeck(int);
};