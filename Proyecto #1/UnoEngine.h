#pragma once
#include <SFML/Graphics.hpp>
#include "CardsDeck.h"

using namespace sf;

void startMenu();
void startGame();

void printCard(UnoCard, int, int);
void refreshWindow(int*, int*, int, int);
void addCardAction(int, bool);
void actionCard(UnoCard, int, bool);
void takeActionCard(bool);
void changeColorAction();
void loopRefresh();

bool mouseDetect(Vector2i, Vector2f, Vector2f);
bool isClickingCard(int, int);
bool verifyCard(UnoCard);
bool skipTurn();