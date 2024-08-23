#pragma once
#include "SetStruct.h"
#include "usefull_sfml.h"
#include "ParametrsGame.h"
#include "Physics.h"

using namespace std;
using namespace sf;

struct ComplexFields {
	Vector2f size = Vector2f(Pr::sz / 2 - 20, Pr::sz / 2 - 20);
	cellka global = cellka(0, 0);;
	Vector2f local = Vector2f(Pr::sz / 2, Pr::sz - size.y);
	Vector2f speed = Vector2f(0, 0);

	Vector2f pos = Vector2f(((Pr::lengthj) / 2 + 0.5) * Pr::sz, ((Pr::lengthi) / 2 + 0.5) * Pr::sz);
	CircleShape pmain = InitialCircleShape(2, Color::Red, pos);
	CircleShape pTL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y - size.y)), pTR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y - size.y));
	CircleShape pBL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y + size.y)), pBR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y + size.y));

	ComplexFields(){}
};