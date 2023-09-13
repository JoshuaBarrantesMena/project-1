#pragma once
#include "UnoCard.h"

class CardsDeck { //mazo para juego: mazo para jugadores

private:

	int size;
	UnoCard* deck; //dinamico

public:
	CardsDeck();
	CardsDeck(int);
	~CardsDeck();
	void fillDeck();
	void deckShufle();
	void setCardDeck(UnoCard, int);
	void setCardInUse(int, bool);
	UnoCard getCardDeck(int);


	void print();
};