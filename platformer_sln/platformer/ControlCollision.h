#pragma once
#include "ObjectMapa.h"

struct TLRB {
    bool top = false;
    bool left = false;
    bool right = false;
    bool bottom = false;
};
struct mapaTLRB {
    Object* T;
    Object* L;
    Object* R;
    Object* B;

    mapaTLRB(Object* top,Object* left, Object* right, Object* bottom):T{top},L{left},R{right},B{bottom} {}
    ~mapaTLRB(){}
};
struct ControlCollision {
    Vector2f size = Vector2f(Pr::sz / 2 - 20, Pr::sz / 2 - 20);
    Vector2f posmain = Vector2f(((Pr::lengthj) / 2 + 0.5) * Pr::sz, ((Pr::lengthi) / 2 + 0.5) * Pr::sz);
    CircleShape pmain = InitialCircleShape(2, Color::Red, posmain);
    CircleShape pTL = InitialCircleShape(2, Color::Red, Vector2f(posmain.x - size.x, posmain.y - size.y)), pTR = InitialCircleShape(2, Color::Red, Vector2f(posmain.x + size.x, posmain.y - size.y));
    CircleShape pBL = InitialCircleShape(2, Color::Red, Vector2f(posmain.x - size.x, posmain.y + size.y)), pBR = InitialCircleShape(2, Color::Red, Vector2f(posmain.x + size.x, posmain.y + size.y));

    ControlCollision() {}
    ~ControlCollision() {}

    TLRB Collision(mapaTLRB set,cellka gl, Vector2f loc, Vector2f speed) {
        TLRB res;
        Pos pTL(gl, loc), pTR(gl, loc), pBL(gl, loc), pBR(gl, loc);
        pTL.Move(Vector2f(-size.x, -size.y)); pTR.Move(Vector2f(+size.x, -size.y));
        pBL.Move(Vector2f(-size.x, +size.y)); pBR.Move(Vector2f(+size.x, +size.y));

        bool CollisionTL_T = set.T->Collision(pTL.local.y, speed.y, 1);
        bool CollisionTR_T = set.T->Collision(pTR.local.y, speed.y, 1);

        bool CollisionTL_L = set.L->Collision(pTL.local.x, speed.x, 1);
        bool CollisionBL_L = set.L->Collision(pBL.local.x, speed.x, 1);

        bool CollisionTR_R = set.R->Collision(pTR.local.x, speed.x, 0);
        bool CollisionBR_R = set.R->Collision(pBR.local.x, speed.x, 0);

        bool CollisionBL_B = set.B->Collision(pBL.local.y, speed.y, 0);
        bool CollisionBR_B = set.B->Collision(pBR.local.y, speed.y, 0);

        res.top = CollisionTL_T || CollisionTR_T;
        res.left = CollisionTL_L || CollisionBL_L;
        res.right = CollisionTR_R || CollisionBR_R;
        res.bottom = CollisionBL_B || CollisionBR_B;

        return res;
    }
};