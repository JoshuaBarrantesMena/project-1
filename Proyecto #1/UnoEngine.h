#pragma once
#include <SFML/Graphics.hpp>
#include "CardsDeck.h"

using namespace sf;

void startMenu();
void startGame();
bool mouseDetect(Vector2i, Vector2f, Vector2f);
void loopRefresh();
void printCard(UnoCard, Sprite, int, int);