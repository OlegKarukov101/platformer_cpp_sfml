#pragma once
#include <SFML/Graphics.hpp>
#include "OwnGCF.h"
#include "ParametrsGame.h"
using namespace sf;

 
enum class Type{Empty, Block, Slope,Teleport};

class Object {
protected:
	Type tp;
public:
	Object(Type tp) :tp{ tp } {}
	virtual Type getType() = 0;
	virtual bool Collision(float loc, float speed, bool TorL) = 0;
	virtual void setTexture(Texture* texture) = 0;
	virtual void setPosition(Vector2f pos) = 0;
	virtual RectangleShape getShape() = 0;
	~Object() {}
};

class Empty : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(130, 255, 255), Vector2f(0, 0));
public:
	Empty() :Object{ Type::Empty } {}
	Empty(Color col) :Object{ Type::Empty } {
		shape.setFillColor(col);
	}
	Empty(Texture* texture) :Object{ Type::Empty } {
		shape.setTexture(texture);
	}
	Type getType() override { return tp; }
	bool Collision(float loc, float speed, bool TorL) override {
		return false;
	}
	void setTexture (Texture* texture) override {
		shape.setTexture(texture);
	}
	void setPosition(Vector2f pos) override{
		shape.setPosition(pos);
	}
	RectangleShape getShape() override {
		return shape;
	}
	~Empty() {}
};

class Block : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(255, 255, 255), Vector2f(0, 0));
public:
	Block():Object{Type::Block} {}
	Block(Color col) :Object{ Type::Block } {
		shape.setFillColor(col);
	}
	Block(Texture* texture) :Object{ Type::Block } {
		shape.setTexture(texture);
	}
	Type getType() override { return tp; }
	bool Collision(float loc, float speed, bool TorL) override {
		if (TorL) {
			return (this->getFillColor() == Color(255, 255, 255) && (loc + speed) <= 0);
		}
		else {
			return (this->getFillColor() == Color(255, 255, 255) && (loc + speed - Pr::sz) >= 0);
		}
	}
	void setTexture(Texture* texture) override{
		shape.setTexture(texture);
	}
	void setPosition(Vector2f pos) override{
		shape.setPosition(pos);
	}
	RectangleShape getShape() override{
		return shape;
	}
	void setFillColor(Color col) {
		shape.setFillColor(col);
	}
	Color getFillColor() {
		return shape.getFillColor();
	}
	~Block() {}
};
