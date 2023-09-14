#pragma once
#include <SFML/Graphics.hpp>
#include "CardsDeck.h"

using namespace sf;

void startMenu();
void startGame();
bool mouseDetect(Vector2i, Vector2f, Vector2f);
bool isClickingCard(int, int);
void loopRefresh();
void printCard(UnoCard, Sprite, Sprite, int, int);