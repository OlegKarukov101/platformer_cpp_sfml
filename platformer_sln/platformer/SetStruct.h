#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct cellka { //cell-€чейка, клетка, а cellka чисто € придумал - клеточка, €чейка.
    int i = 0, j = 0;//i - y; j - x.
    cellka() {}
    cellka(int i, int j) {
        this->i = i;
        this->j = j;
    };
};


