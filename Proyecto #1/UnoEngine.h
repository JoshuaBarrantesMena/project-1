#pragma once
#include <SFML/Graphics.hpp>
#include "CardsDeck.h"

using namespace sf;

bool mouseDetect(Vector2i, Vector2f, Vector2f);
bool isClickingCard(int, int);
bool verifyCard(UnoCard);
void startMenu();
void startGame();
void printCard(UnoCard, Sprite, Sprite, int, int);
void loopRefresh();