#pragma once
#include <iostream>

using namespace std;

class UnoCard {

private:

	int number; //numero
	char color; //color
	char type; //tipo (si es numero, o comodin)
	bool cardInUse; //si esta en uso o no

public:

	UnoCard(int, char, char, bool);
	UnoCard();
	~UnoCard();

	int getNumber();
	char getColor();
	char getType();
	bool getInUse();

	void setCardInUse(bool);

	void print();

	UnoCard& operator=(UnoCard);
};