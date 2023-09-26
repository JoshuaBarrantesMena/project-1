#include "UnoCard.h"

UnoCard::UnoCard() {

	number = -1;
	color = 'X';
	type = 'v';

}

UnoCard::UnoCard(int pNumber, char pColor, char pType) {

	this->number = pNumber;
	this->color = pColor;
	this->type = pType;
}

UnoCard::~UnoCard() {

}

int UnoCard::getNumber() {

	return number;
}

char UnoCard::getColor() {

	return color;
}

char UnoCard::getType() {

	return type;
}

void UnoCard::setColor(char pColor) {

	color = pColor;
}

UnoCard& UnoCard::operator=(UnoCard card) {

	number = card.getNumber();
	color = card.getColor();
	type = card.getType();

	return *this;
}