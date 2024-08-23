#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SetStruct.h"

using namespace std;
using namespace sf;

RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position);
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness);
CircleShape InitialCircleShape(float radius, Color color, Vector2f position);
CircleShape InitialCircleShape(float radius, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness);
Text InitialText(Text text, Vector2f position, Color TextColor, float OutlineThikness, Color OutlineColor);

