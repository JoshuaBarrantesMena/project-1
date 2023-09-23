#include "UnoCard.h"

UnoCard::UnoCard(int number, char color, char type, bool isInUse) {

	this->number = number;
	this->color = color;
	this->type = type;
	this->cardInUse = isInUse; 
}

UnoCard::UnoCard() {

	number = -1;
	color = 'X';
	type = 'v';
	cardInUse = false;

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

bool UnoCard::getInUse() {

	return cardInUse;
}

void UnoCard::setCardInUse(bool isInUse) {

	cardInUse = isInUse;
} // quitar

UnoCard& UnoCard::operator=(UnoCard card) {

	number = card.getNumber();
	color = card.getColor();
	type = card.getType();
	cardInUse = card.getInUse();

	return *this;
}

void UnoCard::print() {

	cout << "numero [ " << number << " ]";
	cout << "color [ " << color << " ]";
	cout << "tipo [ " << type << " ]";

}