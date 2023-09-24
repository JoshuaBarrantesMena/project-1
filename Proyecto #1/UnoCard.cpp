#include "UnoCard.h"

UnoCard::UnoCard() {

	number = -1;
	color = 'X';
	type = 'v';

}

UnoCard::UnoCard(int number, char color, char type) {

	this->number = number;
	this->color = color;
	this->type = type;
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

void UnoCard::print() {

	cout << "numero [ " << number << " ]";
	cout << "color [ " << color << " ]";
	cout << "tipo [ " << type << " ]";

}

UnoCard& UnoCard::operator=(UnoCard card) {

	number = card.getNumber();
	color = card.getColor();
	type = card.getType();

	return *this;
}