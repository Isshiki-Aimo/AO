//
// Created by Aimo on 2022/5/24.
//

#include <fstream>
#include <cstdlib>
#include "Particle.h"

using namespace std;

float Particle::Xmax = 30.0;
float Particle::Xmin = 0.0;
float Particle::Ymax = 30.0;
float Particle::Ymin = 0.0;
float Particle::Vxmax = Xmax - Xmin;
float Particle::Vxmin = 0.0 - Vxmax;
float Particle::Vymax = Ymax - Ymin;
float Particle::Vymin = 0.0 - Vymax;

float Particle::c1 = 2.0;
float Particle::c2 = 2.0;

Particle::Particle(float x, float y)
{
    //初始位置
    c.x = x;
    c.y = y;

    //初始适应度
    p = pow(c.x-10.0, 2) + pow(c.y-20.0, 2);

    //初始速度
    Vx = (Xmax - Xmin) / 8.0;
    Vy = (Ymax - Ymin) / 8.0;

    //初始的pBest;
    pBest.x = x;
    pBest.y = y;
}

void Particle::setP()
{
    float tmp = pow(c.x-10.0, 2) + pow(c.y-20.0, 2);

    if(tmp < p)
    {
        p = tmp;
        pBest = c;
    }
}

float Particle::getP()
{
    return p;
}

Coordinate Particle::getPBest() const
{
    return pBest;
}

void Particle::setV(Coordinate gBest, float w)
{
    float r1, r2;

    r1 = rand() / (float)RAND_MAX;
    r2 = rand() / (float)RAND_MAX;

    Vx = w * Vx + c1 * r1 * (pBest.x - c.x) + c2 * r2 * (gBest.x - c.x);

    if(Vx > Vxmax)
    {
        Vx = Vxmax;
    }
    else if(Vx < Vxmin)
    {
        Vx = Vxmin;
    }

    Vy = w * Vy + c1 * r1 * (pBest.y - c.y) + c2 * r2 * (gBest.y - c.y);

    if(Vy > Vymax)
    {
        Vy = Vymax;
    }
    else if(Vy < Vymin)
    {
        Vy = Vymin;
    }
}

float Particle::getVx()
{
    return Vx;
}

float Particle::getVy()
{
    return Vy;
}

void Particle::setCoordinate()
{
    c.x = c.x + Vx;

    if(c.x > Xmax)
    {
        c.x = Xmax;
    }
    else if(c.x < Xmin)
    {
        c.x = Xmin;
    }

    c.y = c.y + Vy;

    if(c.y > Ymax)
    {
        c.y = Ymax;
    }
    else if(c.y < Ymin)
    {
        c.y = Ymin;
    }
}

float Particle::getX() const
{
    return c.x;
}

float Particle::getY() const
{
    return c.y;
}

void Particle::outputFile(char Dir[])
{
    cout << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
}

ostream &operator<<(ostream &output, const Particle &right)
{
    output << "Now the current coordinate is X: " << right.getX() << ", Y: " << right.getY() << endl;
    output << "And the pBest is X: " << right.getPBest().x << ", Y: " << right.getPBest().y << endl;
}
