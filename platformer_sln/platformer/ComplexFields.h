#pragma once
#include "SetStruct.h"
#include "usefull_sfml.h"
#include "ParametrsGame.h"
#include "Physics.h"

using namespace std;
using namespace sf;


Vector2f ReCountLocalPos(Vector2f local, Vector2f speed) {
	int sz = Pr::sz;
	float signx = 0, signy = 0;
	if (speed.x != 0)  signx = (speed.x / abs(speed.x));  if (speed.y != 0) signy = (speed.y / abs(speed.y));
	local.x += speed.x + signx * (sz * floor((speed.x) / sz));  local.x = local.x - sz * floor(local.x / sz);
	local.y += speed.y + signy * (sz * floor((speed.y) / sz));  local.y = local.y - sz * floor(local.y / sz);
	return local;
}
cellka ReCountGlobalPos(cellka global, Vector2f local, Vector2f speed) {
	int sz = Pr::sz;
	if (speed.x > 0) {
		global.j += ((int)(speed.x + local.x) / sz);
	}
	else { global.j += ((int)(speed.x + -(sz - local.x)) / sz); }
	if (speed.y > 0) { global.i += ((int)(speed.y + local.y) / sz); }
	else { global.i += ((int)(speed.y + -(sz - local.y)) / sz); }
	return global;
}

class ComplexFields {
public:
	Vector2f size = Vector2f(Pr::sz / 2 - 20, Pr::sz / 2 - 20);
	cellka global = cellka(0, 0);;
	Vector2f local = Vector2f(Pr::sz / 2, Pr::sz - size.y);
	Vector2f speed = Vector2f(0, 0);

	Vector2f pos = Vector2f(((Pr::lengthj) / 2 + 0.5) * Pr::sz, ((Pr::lengthi) / 2 + 0.5) * Pr::sz);
	CircleShape pmain = InitialCircleShape(2, Color::Red, pos);
	CircleShape pTL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y - size.y)), pTR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y - size.y));
	CircleShape pBL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y + size.y)), pBR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y + size.y));

	ComplexFields() {}
	
	void Move(){
		global = ReCountGlobalPos(global, local, speed);
		local = ReCountLocalPos(local, speed);
	}
	~ComplexFields() {}
};