#include<iostream>
#include <cstring>
#include <cassert>
#pragma once
#include<map>
#include<cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include "colors.h"
#include"piece.h"
using namespace std;
#define RONG 10
#define CAO 22
#define DO_PHONG_DAI  30
const unsigned int tocdo[] = {36,32,29,25,22,18,15,11,7,5,4,3,2,1};//Tetris (NES, Nintendo)
const float tocdoframe = 0.05;
class Tetromino
{
    public:
       const unsigned int *khoihinh;
       const int side;
};


