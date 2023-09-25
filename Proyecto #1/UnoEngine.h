#pragma once
#include <SFML/Graphics.hpp>
#include "CardsDeck.h"

using namespace sf;

void startMenu();
void startGame();
void printCard(UnoCard, Sprite, Sprite, int, int);
void refreshWindow(int*, int*, int, int);
void loopRefresh();
bool mouseDetect(Vector2i, Vector2f, Vector2f);
bool isClickingCard(int, int);
bool verifyCard(UnoCard);

void actionCard(UnoCard, int, bool);
//changeColorAction();
//addCardAction(int);
//takeCardAction();