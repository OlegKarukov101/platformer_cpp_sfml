#pragma once 
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "ParametrsGame.h"
#include "ObjectMapa.h"
using namespace sf;

extern vector<vector<Object*>> mapa(300, vector<Object*>(300, new Empty()));