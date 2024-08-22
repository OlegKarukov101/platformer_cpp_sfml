#pragma once
#include "Hero.h"
using namespace std;
using namespace sf;


    Hero::Hero(shared_ptr<RenderWindow> window) {
        this->window = window;
    }
    RectangleShape Hero::getShape() { return shape; }
    Vector2f Hero::getLocalPos() { return localpos; }
    cellka Hero::getGlobalPosMapa() { return globalposmapa; }
    void Hero::setSpeed(Vector2f speed) { this->speed = speed; }
    void Hero::setGlobalPosMapa(cellka pos) {
        globalposmapa = pos;
    }
    void Hero::AddSpeedx(float speedx) {
        speed.x += speedx;
        if (abs(speed.x) > Physics::maxSpeedx)
            speed.x -= speedx;
    }
    void Hero::AddSpeedy(float speedy) {
        speed.y += speedy;
        if (abs(speed.y) > Physics::maxSpeedy) speed.y -= speedy;
    }
    bool Hero::isGround_() { return isGround; }
    void Hero::Collision() {
        cellka gl = globalposmapa;
        Vector2f loc = localpos;
        //Vector2f touchTL(localpos.x - size.x, localpos.y - size.y), touchTR(localpos.x + size.x, localpos.y - size.y);
        //Vector2f touchBL(localpos.x - size.x, localpos.y + size.y), touchBR(localpos.x + size.x, localpos.y + size.y);
        cellka glTL = ReCountGlobalPos(gl, loc, Vector2f(-size.x, -size.y));
        cellka glTR = ReCountGlobalPos(gl, loc, Vector2f(+size.x, -size.y));
        cellka glBL = ReCountGlobalPos(gl, loc, Vector2f(-size.x, +size.y));
        cellka glBR = ReCountGlobalPos(gl, loc, Vector2f(+size.x, +size.y));
        Vector2f locTL = ReCountLocalPos(loc, Vector2f(-size.x, -size.y));
        Vector2f locTR = ReCountLocalPos(loc, Vector2f(+size.x, -size.y));
        Vector2f locBL = ReCountLocalPos(loc, Vector2f(-size.x, +size.y));
        Vector2f locBR = ReCountLocalPos(loc, Vector2f(+size.x, +size.y));

        bool CollisionTL_T = mapa[glTL.i - 1][glTL.j]->Collision(locTL.y, speed.y, 1);
        bool CollisionTR_T = mapa[glTR.i - 1][glTR.j]->Collision(locTR.y, speed.y, 1);

        bool CollisionTL_L = mapa[glTL.i][glTL.j - 1]->Collision(locTL.x, speed.x, 1);
        bool CollisionBL_L = mapa[glBL.i][glBL.j - 1]->Collision(locBL.x, speed.x, 1);

        bool CollisionTR_R = mapa[glTR.i][glTR.j + 1]->Collision(locTR.x, speed.x, 0);
        bool CollisionBR_R = mapa[glBR.i][glBR.j + 1]->Collision(locBR.x, speed.x, 0);

        bool CollisionBL_B = mapa[glBL.i + 1][glBL.j]->Collision(locBL.y, speed.y, 0);
        bool CollisionBR_B = mapa[glBR.i + 1][glBR.j]->Collision(locBR.y, speed.y, 0);

        bool topCollision = CollisionTL_T || CollisionTR_T;
        bool leftCollision = CollisionTL_L || CollisionBL_L;
        bool rightCollision = CollisionTR_R || CollisionBR_R;
        bool bottomCollision = CollisionBL_B || CollisionBR_B;
        if (bottomCollision) {
            isGround = true;
        }
        else isGround = false;

        if (rightCollision && speed.x > 0) {
            speed.x = 0;
        }
        if (leftCollision && speed.x < 0) {
            speed.x = 0;
        }
        if (topCollision && speed.y < 0) { speed.y = 0; }
        if (isGround && speed.y > 0) { speed.y = 0; };

        /*if (rightWall && (Pr::sz - (localpos.x + speed.x)) < size.x && speed.x>0) { speed.x = (Pr::sz - localpos.x) - size.x; }
        if (leftWall && (localpos.x+speed.x) < size.x && speed.x<0) { speed.x = -localpos.x+size.x; }
        if (topWall && (localpos.y+speed.y) < size.y && speed.y<0) { speed.y = -localpos.y+size.y; }
        if (isGround && speed.y > 0) { speed.y = (Pr::sz-localpos.y)-size.y; };*/

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
    void Hero::UpdateHero() {

        if (!isGround) {
            speed.y += Physics::gravity;
            if (speed.x != 0) {
                if (speed.x > 0)
                    speed.x -= Physics::airFriction;

                else if (speed.x < 0)
                    speed.x += Physics::airFriction;
            }
        }
        else {
            if (speed.x != 0) {
                if (speed.x > 0)
                    speed.x -= Physics::groundFriction;
                else if (speed.x < 0)
                    speed.x += Physics::groundFriction;

                if (abs(speed.x) < Physics::groundFriction) speed.x = 0;
            }
        }
        Collision();
        mapa[globalposmapa.i][globalposmapa.j]->Enteraction(this);
        int sz = Pr::sz;

        /*if (speed.x>0) {
            globalposmapa.j += floor((speed.x + localpos.x) / sz); }
        else { globalposmapa.j += floor((speed.x + -(sz-localpos.x)) / sz); }
        if (speed.y > 0) { globalposmapa.i += floor((speed.y + localpos.y) / sz); }
        else { globalposmapa.i += floor((speed.y + -(sz - localpos.y)) / sz); }*/
        /*float signx = 0, signy = 0;
        if (speed.x != 0)  signx = (speed.x / abs(speed.x));  if(speed.y!=0) signy = (speed.y / abs(speed.y));
        localpos.x += speed.x + signx*(sz * floor((speed.x) / sz));  localpos.x = localpos.x - sz*floor(localpos.x/sz);
        localpos.y += speed.y + signy*(sz * floor((speed.y) / sz));  localpos.y = localpos.y - sz*floor(localpos.y/sz);*/
        globalposmapa = ReCountGlobalPos(globalposmapa, localpos, speed);
        localpos = ReCountLocalPos(localpos, speed);

        pair<int, int> pr(globalposmapa.i, globalposmapa.j);
        if (tep1.first == pr) {
            globalposmapa.i = tep1.second.first;
            globalposmapa.j = tep1.second.second;
        }
        //else if (tep1.second == pr) { shape.setPosition(mapa[tep1.first.first][tep1.first.second].getPosition()); }
        else if (tep2.first == pr) {
            globalposmapa.i = tep2.second.first;
            globalposmapa.j = tep2.second.second;
        }
        //else if (tep2.second == pr) { shape.setPosition(mapa[tep2.first.first][tep2.first.second].getPosition()); }*/
    }
    void Hero::Draw() {
        if (window) {
            window->draw(shape);
            window->draw(pmain);
            window->draw(pTL);
            window->draw(pTR);
            window->draw(pBL);
            window->draw(pBR);
        }
    }
    Hero::~Hero() {}
};
