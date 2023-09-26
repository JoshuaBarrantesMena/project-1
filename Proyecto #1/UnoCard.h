#pragma once
#include <iostream>

using namespace std;

class UnoCard {

private:

	int number;
	char color;
	char type;

public:

	UnoCard();
	UnoCard(int, char, char);
	~UnoCard();

	int getNumber();
	char getColor();
	char getType();
	void setColor(char);

	UnoCard& operator=(UnoCard);
};