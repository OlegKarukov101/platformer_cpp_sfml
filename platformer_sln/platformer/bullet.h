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
    shared_ptr<RenderWindow> window;
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
        this->window = window;
    }

    void Move() {
        bul.move(Vector2f((direction ? bulletSpeed : -bulletSpeed), 0));
        Draw();
    }

    void Destroy() {
        DeleteBullet(this);
        delete(this);
    }
    void Draw() {
        window->draw(bul);
    }
    ~Bullet() {
        // Destructor will be called when the object is destroyed, so manage your resources here if necessary
    }
};