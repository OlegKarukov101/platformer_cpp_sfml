#pragma once
#include "Hero.h"



    Hero::Hero(shared_ptr<RenderWindow> window) {
        this->window = window;
    }
    RectangleShape Hero::getShape() { return shape; }
    Vector2f Hero::getLocalPos() { return cf.local; }
    cellka Hero::getGlobalPosMapa() { return cf.global; }
    void Hero::setSpeed(Vector2f speed) { this->cf.speed = speed; }
    void Hero::setGlobalPosMapa(cellka pos) {
        cf.global = pos;
    }
    Vector2f Hero::getPos() {
        return shape.getPosition();
    }
    void Hero::AddSpeedx(float speedx) {
        cf.speed.x += speedx;
        if (abs(cf.speed.x) > Physics::maxSpeedx)
            cf.speed.x -= speedx;
    }
    void Hero::AddSpeedy(float speedy) {
        cf.speed.y += speedy;
        if (abs(cf.speed.y) > Physics::maxSpeedy) cf.speed.y -= speedy;
    }
    bool Hero::isGround_() { return isGround; }
    void Hero::Collision(Object* mapaT, Object* mapaL, Object* mapaR, Object* mapaB) {
        cellka gl = cf.global;
        Vector2f loc = cf.local;
        
        cellka glTL = ReCountGlobalPos(gl, loc, Vector2f(-cf.size.x, -cf.size.y));
        cellka glTR = ReCountGlobalPos(gl, loc, Vector2f(+cf.size.x, -cf.size.y));
        cellka glBL = ReCountGlobalPos(gl, loc, Vector2f(-cf.size.x, +cf.size.y));
        cellka glBR = ReCountGlobalPos(gl, loc, Vector2f(+cf.size.x, +cf.size.y));
        Vector2f locTL = ReCountLocalPos(loc, Vector2f(-cf.size.x, -cf.size.y));
        Vector2f locTR = ReCountLocalPos(loc, Vector2f(+cf.size.x, -cf.size.y));
        Vector2f locBL = ReCountLocalPos(loc, Vector2f(-cf.size.x, +cf.size.y));
        Vector2f locBR = ReCountLocalPos(loc, Vector2f(+cf.size.x, +cf.size.y));

        bool CollisionTL_T = mapaT->Collision(locTL.y, cf.speed.y, 1);
        bool CollisionTR_T = mapaT->Collision(locTR.y, cf.speed.y, 1);

        bool CollisionTL_L = mapaL->Collision(locTL.x, cf.speed.x, 1);
        bool CollisionBL_L = mapaL->Collision(locBL.x, cf.speed.x, 1);

        bool CollisionTR_R = mapaR->Collision(locTR.x, cf.speed.x, 0);
        bool CollisionBR_R = mapaR->Collision(locBR.x, cf.speed.x, 0);

        bool CollisionBL_B = mapaB->Collision(locBL.y, cf.speed.y, 0);
        bool CollisionBR_B = mapaB->Collision(locBR.y, cf.speed.y, 0);

        bool topCollision = CollisionTL_T || CollisionTR_T;
        bool leftCollision = CollisionTL_L || CollisionBL_L;
        bool rightCollision = CollisionTR_R || CollisionBR_R;
        bool bottomCollision = CollisionBL_B || CollisionBR_B;
        if (bottomCollision) {
            isGround = true;
        }
        else isGround = false;

        if (rightCollision && cf.speed.x > 0) {
            cf.speed.x = 0;
        }
        if (leftCollision && cf.speed.x < 0) {
            cf.speed.x = 0;
        }
        if (topCollision && cf.speed.y < 0) { cf.speed.y = 0; }
        if (isGround && cf.speed.y > 0) { cf.speed.y = 0; };

       

    }


#pragma region direction
    bool Hero::GetDirection() { return _direction; }
    void Hero::SetDirection(bool value) { _direction = value; }
#pragma endregion

    void Hero::UpdateHero(Object* mapaMain, Object* mapaT, Object* mapaL, Object* mapaR, Object* mapaB) {

        if (!isGround) {
            cf.speed.y += Physics::gravity;
            if (cf.speed.x != 0) {
                if (cf.speed.x > 0)
                    cf.speed.x -= Physics::airFriction;

                else if (cf.speed.x < 0)
                    cf.speed.x += Physics::airFriction;
            }
        }
        else {
            if (cf.speed.x != 0) {
                if (cf.speed.x > 0)
                    cf.speed.x -= Physics::groundFriction;
                else if (cf.speed.x < 0)
                    cf.speed.x += Physics::groundFriction;

                if (abs(cf.speed.x) < Physics::groundFriction) cf.speed.x = 0;
            }
        }
        Collision(mapaT,mapaL,mapaR,mapaB);
        cf = mapaMain->Enteraction(&cf);
        
        cf.Move();

        
    }
    void Hero::Draw() {
        if (window) {
            window->draw(shape);
            window->draw(cf.pmain);
            window->draw(cf.pTL);
            window->draw(cf.pTR);
            window->draw(cf.pBL);
            window->draw(cf.pBR);
        }
    }
    Hero::~Hero() {}
    

