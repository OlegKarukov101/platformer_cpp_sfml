#pragma once
#include "ObjectMapa.h"
#include "ComplexFields.h"
using namespace std;
using namespace sf;


class Hero {
private:
	shared_ptr<RenderWindow> window;
	ComplexFields cf;
	//cellka globalposmapa = cellka(0, 0);
	bool isGround = true;
	bool _direction = true;//false(0) - left, true(1) - right
	//Vector2f size = Vector2f(Pr::sz / 2 - 20, Pr::sz / 2 - 20);
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz - 40, Pr::sz - 40), Color(0, 0, 0), Vector2f(((Pr::lengthj) / 2 + 0.5) * Pr::sz, ((Pr::lengthi) / 2 + 0.5) * Pr::sz), 1, Color(220, 50, 50));
	//Vector2f pos = shape.getPosition();
	//CircleShape pmain = InitialCircleShape(2, Color::Red, pos);
	//CircleShape pTL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y - size.y)), pTR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y - size.y));
	//CircleShape pBL = InitialCircleShape(2, Color::Red, Vector2f(pos.x - size.x, pos.y + size.y)), pBR = InitialCircleShape(2, Color::Red, Vector2f(pos.x + size.x, pos.y + size.y));
	//Vector2f speed = Vector2f(0, 0);
	//Vector2f localpos = Vector2f(Pr::sz / 2, Pr::sz - size.y);
public:
	Hero(shared_ptr<RenderWindow> window);
	RectangleShape getShape();
	Vector2f getLocalPos();
	cellka getGlobalPosMapa();
	void setSpeed(Vector2f speed);
	void setGlobalPosMapa(cellka pos);
	void AddSpeedx(float speedx);
	void AddSpeedy(float speedy);
	bool isGround_();
	bool GetDirection();
	Vector2f getPos();
	void SetDirection(bool value);
	void Collision(Object* mapaT, Object* mapaL, Object* mapaR, Object* mapaB);
	//Vector2f ReCountLocalPos(Vector2f localpos, Vector2f speed);
	//cellka ReCountGlobalPos(cellka globalposmapa, Vector2f localpos, Vector2f speed);
	void UpdateHero(Object* mapaMain, Object* mapaT, Object* mapaL, Object* mapaR, Object* mapaB);
	void Draw();
	~Hero();
};

