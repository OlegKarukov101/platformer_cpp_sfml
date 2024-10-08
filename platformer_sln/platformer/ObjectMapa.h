#pragma once
#include "SetStruct.h"
#include "usefull_sfml.h"
#include "ParametrsGame.h"
#include "Physics.h"
#include "ComplexFields.h"
using namespace sf;

 
enum class Type{Empty, Block, Slope, Teleport};

class Object {
protected:
	Type tp;
	shared_ptr<RenderWindow> window;
public:
	Object() {}
	Object(shared_ptr<RenderWindow> window, Type tp) :tp{ tp } { this->window = window; }
	virtual Type getType() = 0;
	virtual bool Collision(float loc, float speed, bool TorL) = 0;
	virtual ComplexFields Enteraction(ComplexFields* cf) = 0;
	virtual void setTexture(Texture* texture) = 0;
	virtual void setPosition(Vector2f pos) = 0;
	virtual void setFillColor(Color col) = 0;
	virtual void Draw() = 0;

	~Object() {}
};

class Empty : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(130, 255, 255), Vector2f(0, 0));
public:
	Empty() {

	}
	Empty(shared_ptr<RenderWindow> window) :Object{window, Type::Empty } {}
	Empty(shared_ptr<RenderWindow> window, Color col) :Object{window, Type::Empty } {
		shape.setFillColor(col);
	}
	Empty(shared_ptr<RenderWindow> window, Texture* texture) :Object{window, Type::Empty } {
		shape.setTexture(texture);
	}
	Type getType() override { return tp; }
	bool Collision(float loc, float speed, bool checkTOPorLEFT) override {
		return false;
	}
	ComplexFields Enteraction(ComplexFields* cf) override { return *cf; }
	void setTexture (Texture* texture) override {
		shape.setTexture(texture);
	}
	void setPosition(Vector2f pos) override{
		shape.setPosition(pos);
	}
	void setFillColor(Color col) override {
		shape.setFillColor(col);
	}
	void Draw() override{ window->draw(shape); }
	~Empty() {}
};

class Block : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(255, 255, 255), Vector2f(0, 0));
public:
	Block(shared_ptr<RenderWindow> window):Object{window,Type::Block} {}
	Block(shared_ptr<RenderWindow> window, Color col) :Object{window, Type::Block } {
		shape.setFillColor(col);
	}
	Block(shared_ptr<RenderWindow> window, Texture* texture) :Object{window, Type::Block } {
		shape.setTexture(texture);
	}
	Type getType() override { return tp; }
	bool Collision(float loc, float speed, bool TorL) override {
		if (TorL) {
			return (this->getType() == Type::Block && (loc + speed) <= 0);
		}
		else {
			return (this->getType() == Type::Block && (loc + speed - Pr::sz) >= 0);
		}
	}
	ComplexFields Enteraction(ComplexFields* cf) override { return *cf; }
	void setTexture(Texture* texture) override{
		shape.setTexture(texture);
	}
	void setPosition(Vector2f pos) override{
		shape.setPosition(pos);
	}
	void setFillColor(Color col) override{
		shape.setFillColor(col);
	}
	void Draw() override{ window->draw(shape); }
	~Block() {}
};


static Clock tm;
class Teleport : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(255, 255, 255), Vector2f(0, 0));
	cellka coords;
	
public:
	Teleport(shared_ptr<RenderWindow> window,Color col,cellka coords) :Object{ window,Type::Teleport }
	{
		shape.setFillColor(col);
		this->coords = coords;
	}
	Type getType() override { return tp; }
	bool Collision(float loc, float speed, bool TorL) override {//does not collides
		return false;
	}
	void setTexture(Texture* texture) override {
		shape.setTexture(texture);
	}
	ComplexFields Enteraction(ComplexFields* cf) override{
		float time = tm.restart().asSeconds();
		cout << time << endl;
		if(time>=1) 
			cf->pos.global = coords;
		return *cf;
	}
	void setPosition(Vector2f pos) override {
		shape.setPosition(pos);
	}
	void setFillColor(Color col) override {
		shape.setFillColor(col);
	}
	void Draw() override { window->draw(shape); }
};
