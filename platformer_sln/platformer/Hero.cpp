#pragma once
#include "Hero.h"
using namespace std;
using namespace sf;


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
    Vector2f Hero::ReCountLocalPos(Vector2f localpos, Vector2f speed) {
        int sz = Pr::sz;
        float signx = 0, signy = 0;
        if (speed.x != 0)  signx = (speed.x / abs(speed.x));  if (speed.y != 0) signy = (speed.y / abs(speed.y));
        localpos.x += speed.x + signx * (sz * floor((speed.x) / sz));  localpos.x = localpos.x - sz * floor(localpos.x / sz);
        localpos.y += speed.y + signy * (sz * floor((speed.y) / sz));  localpos.y = localpos.y - sz * floor(localpos.y / sz);
        return localpos;
    }
    cellka Hero::ReCountGlobalPos(cellka globalposmapa, Vector2f localpos, Vector2f speed) {
        int sz = Pr::sz;
        if (speed.x > 0) {
            globalposmapa.j += ((int)(speed.x + localpos.x) / sz);
        }
        else { globalposmapa.j += ((int)(speed.x + -(sz - localpos.x)) / sz); }
        if (speed.y > 0) { globalposmapa.i += ((int)(speed.y + localpos.y) / sz); }
        else { globalposmapa.i += ((int)(speed.y + -(sz - localpos.y)) / sz); }
        return globalposmapa;
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
        
        cf.global = ReCountGlobalPos(cf.global, cf.local, cf.speed);
        cf.local = ReCountLocalPos(cf.local, cf.speed);

        
        
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
    

