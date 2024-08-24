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
    const float bulletSpeed = 20.0f;
    const float bulletRadius = 15;
    bool direction;
    CircleShape bul;
    static vector<Bullet*> bullets;

public:
#pragma region Working with static
    static void MoveBullets() {
        for (Bullet* b : bullets)
            b->Move();
    }

    void DeleteBullet(Bullet* b) {
        auto it = std::find(bullets.begin(), bullets.end(), b);
        if (it != bullets.end()) {
            bullets.erase(it);
        }
    }
#pragma endregion

    Bullet(shared_ptr<RenderWindow> window, Color col, Vector2f heroPos, bool direction) {
        this->direction = direction;
        bul = InitialCircleShape(bulletRadius, col, heroPos);  // Assuming InitialCircleShape is defined elsewhere
        bullets.push_back(this);
    }

    void Move() {
        bul.move(Vector2f((direction ? bulletSpeed : -bulletSpeed), 0));
    }

    void Destroy() {
        DeleteBullet(this);
        // Do not use delete this; unless you are absolutely sure it was allocated with new
    }

    ~Bullet() {
        // Destructor will be called when the object is destroyed, so manage your resources here if necessary
    }
};