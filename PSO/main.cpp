//
// Created by Aimo on 2022/5/24.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Particle.h"
#include "Information.h"

using namespace std;

int main() {
    Coordinate gBest;
    Particle *particles[CityNum];
    Particle *tmp;
    float w;
    float rand_x, rand_y;
    float bestP;
    int bestIndex = 0;

    srand((int) time(NULL));

    for (int i = 0; i < CityNum; i++) {
        rand_x = City_x[i];
        rand_y = City_y[i];

        particles[i] = new Particle(rand_x, rand_y);

        cout << "The temp info is X: " << particles[i]->getX() << ", Y: " << particles[i]->getY() << endl;
    }

    bestP = particles[0]->getP();
    gBest = particles[0]->getPBest();

    for (int i = 1; i < CityNum; i++) {
        if (particles[i]->getP() < bestP) {
            bestP = particles[i]->getP();
            gBest = particles[i]->getPBest();
            bestIndex = i;
        }
    }

    cout << "Now the initial gBest is X: " << gBest.x << ", Y: " << gBest.y << endl;

    for (int k = 0; k < 100; k++) {
        w = 0.9 - (0.9 - 0.4) * k / 99.0;

        for (int i = 0; i < 40; i++) {
            tmp = particles[i];
            tmp->setV(gBest, w);
            tmp->setCoordinate();
            tmp->setP();
        }

        bestP = particles[0]->getP();
        gBest = particles[0]->getPBest();
        bestIndex = 0;

        for (int i = 1; i < 40; i++) {
            if (particles[i]->getP() < bestP) {
                bestP = particles[i]->getP();
                gBest = particles[i]->getPBest();
                bestIndex = i;
            }
        }

        cout << "Now the gBest is X: " << gBest.x << ", Y: " << gBest.y << endl;
    }

    return 0;
}
