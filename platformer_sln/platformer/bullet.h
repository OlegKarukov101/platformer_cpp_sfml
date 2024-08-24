#pragma ones
#include "ObjectMapa.h"
#include "ComplexFields.h"
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;
using namespace sf;
class Bullet {
protected:
    const float bulletSpeed = 0.0f;
    const float bulletRadius = 15;
    bool direction;
    CircleShape bul;
    
    shared_ptr<RenderWindow> window;

public:

    Bullet(shared_ptr<RenderWindow> window, Color col, Vector2f heroPos, bool direction) {
        this->direction = direction;
        bul = InitialCircleShape(bulletRadius, col, heroPos);  // Assuming InitialCircleShape is defined elsewhere
        
        this->window = window;

    }

    void Move() {
        //cout << bul.getPosition().x <<" " << bul.getPosition().y << endl;
        bul.move(Vector2f((direction ? bulletSpeed : -bulletSpeed), 0));
        //Draw();
    }

    //void Destroy() {
    //    DeleteBullet(this);
    //}

    void Draw() {
        window->draw(bul);
    }
    
    ~Bullet() {
    }
};