//  TODO::скопировать все ассеты в папку с exe средствами CMake 
#include "Physics.h"
#include "ParametrsGame.h"
#include "ObjectMapa.h"
#include "Hero.h"
#include <format>
#include <map>
#include "bullet.h";

using namespace std;
using namespace sf;

#define STRING(x) #x
#define XSTRING(x) STRING(x)
static const string SOURCE_DIR_PATH = XSTRING(SOURCE_ROOT);
vector<Bullet> bullets;
vector<string> infmapa{     "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,  // *  cube 100*100 
                            "############.............................................................................................###################################" ,
                            "############.............................................................................................###################################" ,
                            "############................................1............................3........################1......########..............#############" ,
                            "########################################........######.......#####################################.......########....2###......#############" ,
                            "########################################.....................#######################################................######.....#############" ,
                            "###########................................###..........###..2....................#########################################.......##########" ,
                            "###########......3................................................................##################..............##########......##########" ,
                            "###########.....#########################.....#####.........############..........############....................######1.....##############" ,
                            "#############....######################...#............###################........##########......###########..................#############" ,
                            "##############......###################....#.............####################3.................3############################################" ,
                            "################......o################.........#####....###################################################################################" ,
                            "#################........................####....................2..................................................########################" ,
                            "###################...........2.............................................................################....................1###########" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################",
                            "############################################################################################################################################",
                            "############################################################################################################################################" };
//shared_ptr<RenderWindow> window_ptr = make_shared<RenderWindow>(VideoMode(Pr::windowSizex, Pr::windowSizey), L"Платформер", Style::Default);
vector<vector<Object*>> mapa(300, vector<Object*>(300, new Empty()));
pair<pair<int, int>, pair<int, int>> tep1(pair<int, int>(0, 0), pair<int, int>(0, 0));
pair<pair<int, int>, pair<int, int>> tep2(pair<int, int>(0, 0), pair<int, int>(0, 0));

void DeleteMapa() {
    for (int i = 0; i <= mapa.size(); i++) {
        for (int j = 0; j <= mapa[i].size(); j++) {
            delete mapa[i][j];
        }
    }
}

void UpdateMapa(cellka globalposmapa, Vector2f localposHero) {

    //cout << globalposmapa.i <<"--"<< globalposmapa.j << endl;
    for (int i = 0; i <= Pr::lengthi; i++) { //9 16
        for (int j = 0; j <= Pr::lengthj; j++) {
            mapa[i + globalposmapa.i - (Pr::lengthi) / 2][j + globalposmapa.j - (Pr::lengthj - 1) / 2]->setPosition(Vector2f(-localposHero.x + Pr::sz * (1 + j), -localposHero.y + Pr::sz * (1 + i)));

        }
    }
}
void DrawMapa(shared_ptr<RenderWindow> window, cellka globalposmapa) {
    for (int i = 0; i <= Pr::lengthi; i++) {
        for (int j = 0; j <= Pr::lengthj; j++) {
            //if (mapa[i + globalposmapa.i - (Pr::lengthi) / 2][j + globalposmapa.j - (Pr::lengthj) / 2]->getType() == Type::Block)
                mapa[i + globalposmapa.i - (Pr::lengthi) / 2][j + globalposmapa.j - (Pr::lengthj) / 2]->Draw();
        }
    }
}

int main()
{
    
    shared_ptr<RenderWindow> window_ptr = make_shared<RenderWindow>(VideoMode(Pr::windowSizex, Pr::windowSizey), L"Платформер", Style::Default);

    window_ptr->setVerticalSyncEnabled(true);
    srand((unsigned int)time(0));
    RectangleShape contour = InitialRectangleShape(Vector2f(Pr::windowSizex - 2 * Pr::sz, Pr::windowSizey - 2 * Pr::sz), Color(130, 255, 255, 0), Vector2f(Pr::windowSizex / 2, Pr::windowSizey / 2), Pr::sz, Color(50, 220, 50));
    RectangleShape fon = InitialRectangleShape(Vector2f(Pr::windowSizex, Pr::windowSizey), Color(130, 255, 255), Vector2f(Pr::windowSizex / 2, Pr::windowSizey / 2));
    Hero hero(window_ptr);




    Font fontDays2, fontImpact2;
    //if (fontDays2.loadFromFile("platformer\\assets\\fonts\\days2.ttf")) cout << "YEES fontDays2\n";
    //if (fontImpact2.loadFromFile("platformer\\assets\\fonts\\impact2.ttf")) cout << "YEES fontImpact2\n";
    Texture texture1;
    //if (texture1.loadFromFile("texture1.jpeg",IntRect(10,10,128,128))) cout << "YEEES texture \n";
    if (texture1.loadFromFile(format("{}/assets/textures/texture5.jpeg", SOURCE_DIR_PATH))) cout << "YEEES texture \n";
    //if (texture1.loadFromFile("texture1.jpeg",IntRect(10,10,128,128))) cout << "YEEES texture \n";
    texture1.setSmooth(true);


    map<char,vector<cellka>> tp{
        pair<char,vector<cellka>> {'1',vector<cellka>()},{'2',vector<cellka>()},{'3',vector<cellka>()}
    };
    string stp = "123";
    map<char, Color> coltp {
        pair<char,Color> {'1',Color(220,100,100)},{'2',Color(100,100,220)},{'3',Color(100,220,100)}
    };

    for (int i = 0; i < infmapa.size(); i++) {
        for (int j = 0; j < infmapa[i].size(); j++) {
            mapa[i][j] = new Empty(window_ptr);
            char p = infmapa[i][j];
            if (p == '#') {
                mapa[i][j] = new Block(window_ptr, &texture1);
                
            }
            if (p == 'o') {
                hero.setGlobalPosMapa(cellka(i, j));
            }
            if (stp.find(p) != string::npos) {
                cout << p << ":" << endl;
                vector<cellka> tep = tp[p];
                if (tep.size() > 0) {
                    mapa[tep.back().i][tep.back().j] = new Teleport(window_ptr, coltp[p], cellka(i, j));
                    cout << format("[{}][{}]", tep.back().i, tep.back().j) << " = " << i << "," << j << endl;
                }
                tp[p].push_back(cellka(i, j));
                cout << format("push_back({},{})", i,j)<< endl;
            }
        }
    }
    cout << endl;
    for (const auto& el : tp) {
        mapa[el.second.back().i][el.second.back().j] = new Teleport(window_ptr, coltp[el.first], el.second.front());
        cout << format("[{}][{}]", el.second.back().i, el.second.back().j )<< " = " << el.second.front().i << "," << el.second.front().j << endl;
        cout << el.first << endl;
        for (int i = 0; i < el.second.size(); i++) {
            cout << el.second[i].i << "-" << el.second[i].j << endl;
        }
        cout << endl;
    }









    //commit 2
    //tugtjgutur
    //capusta 3
    //main capusta
    Clock clock;
    float time = (float)clock.getElapsedTime().asSeconds();

    int frame = 0;
    while (window_ptr->isOpen())
    {
        
        frame %= 100000;
        frame++;
        time = clock.getElapsedTime().asSeconds();
        Event event;
        while (window_ptr->pollEvent(event))
        {
            switch (event.type) {
            case Event::Closed:
                DeleteMapa();
                window_ptr->close();
                break;
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Left) {

                }
                break;
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            //if(hero.isGround_()) 
            hero.AddSpeedx(-Physics::Speedx);
            hero.SetDirection(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            //if(hero.isGround_()) 
            hero.AddSpeedx(Physics::Speedx);
            hero.SetDirection(1);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (hero.isGround_())
                hero.AddSpeedy(-Physics::jumpSpeed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            bullets.push_back(Bullet(window_ptr,Color(255,140,10),hero.getLocalPos(), hero.GetDirection()));
        }
        cellka glhero = hero.getGlobalPosMapa();
        hero.UpdateHero(mapa[glhero.i][glhero.j],mapa[glhero.i - 1][glhero.j], mapa[glhero.i][glhero.j-1], mapa[glhero.i][glhero.j+1], mapa[glhero.i+1][glhero.j]);
        UpdateMapa(hero.getGlobalPosMapa(), hero.getLocalPos());
        window_ptr->clear();
        window_ptr->draw(fon);
        DrawMapa(window_ptr, hero.getGlobalPosMapa());
        hero.Draw();
        for (Bullet bul : bullets) {
            bul.Move();
        }
        for (Bullet bul:bullets) { bul.Draw(); }
        
        //window_ptr->draw(contour);
        window_ptr->display();
    }
    return 0;
}