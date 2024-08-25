#pragma once
#include "Hero.h"
using namespace std;
using namespace sf;


    Hero::Hero(shared_ptr<RenderWindow> window) {
        this->window = window;
    }
    RectangleShape Hero::getShape() { return shape; }
    Vector2f Hero::getLocalPos() { return cf.pos.local; }
    cellka Hero::getGlobalPosMapa() { return cf.pos.global; }
    void Hero::setSpeed(Vector2f speed) { this->cf.speed = speed; }
    void Hero::setGlobalPosMapa(cellka pos) {
        cf.pos.global = pos;
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
    /*void Hero::Collision(Object* mapaT, Object* mapaL, Object* mapaR, Object* mapaB) {
        cellka gl = cf.pos.global;
        Vector2f loc = cf.pos.local;
        
        
        Pos pTL(gl, loc), pTR(gl, loc), pBL(gl, loc), pBR(gl, loc);
        pTL.Move(Vector2f(-cf.size.x, -cf.size.y)); pTR.Move(Vector2f(+cf.size.x, -cf.size.y));
        pBL.Move(Vector2f(-cf.size.x, +cf.size.y)); pBR.Move(Vector2f(+cf.size.x, +cf.size.y));

        bool CollisionTL_T = mapaT->Collision(pTL.local.y, cf.speed.y, 1);
        bool CollisionTR_T = mapaT->Collision(pTR.local.y, cf.speed.y, 1);

        bool CollisionTL_L = mapaL->Collision(pTL.local.x, cf.speed.x, 1);
        bool CollisionBL_L = mapaL->Collision(pBL.local.x, cf.speed.x, 1);

        bool CollisionTR_R = mapaR->Collision(pTR.local.x, cf.speed.x, 0);
        bool CollisionBR_R = mapaR->Collision(pBR.local.x, cf.speed.x, 0);

        bool CollisionBL_B = mapaB->Collision(pBL.local.y, cf.speed.y, 0);
        bool CollisionBR_B = mapaB->Collision(pBR.local.y, cf.speed.y, 0);

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

       

    }*/
    void Hero::Collision(TLRB collis) {
        if (collis.bottom) {
            isGround = true;
        }
        else isGround = false;

        if (collis.right && cf.speed.x > 0) {
            cf.speed.x = 0;
        }
        if (collis.left && cf.speed.x < 0) {
            cf.speed.x = 0;
        }
        if (collis.top && cf.speed.y < 0) { cf.speed.y = 0; }
        if (isGround && cf.speed.y > 0) { cf.speed.y = 0; };
    }
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
        Collision(cc.Collision(mapaTLRB(mapaT,mapaL,mapaR,mapaB),cf.pos.global,cf.pos.local,cf.speed));
        cf = mapaMain->Enteraction(&cf);
        
        cf.pos.Move(cf.speed);

        
        
    }
    void Hero::Draw() {
        if (window) {
            window->draw(shape);
            window->draw(cc.pmain);
            window->draw(cc.pTL);
            window->draw(cc.pTR);
            window->draw(cc.pBL);
            window->draw(cc.pBR);
        }
    }
    Hero::~Hero() {}
    

