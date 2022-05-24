//
// Created by Aimo on 2022/5/24.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H
#include <iostream>
#include <math.h>
#include "coordinate.h"

class Particle {
    friend std::ostream &operator<<(std::ostream &output, const Particle &right);
public:
    Particle(float x, float y);
    void setP();
    float getP();

    Coordinate getPBest() const;

    //w为惯性因子
    void setV(Coordinate gBest, float w);
    float getVx();
    float getVy();

    void setCoordinate();
    float getX() const;
    float getY() const;

    void outputFile(char Dir[]);

private:
    Coordinate c;
    //p为适应度
    float p;
    Coordinate pBest;
    float Vx;
    float Vy;

    static float Xmax, Xmin;
    static float Ymax, Ymin;
    static float Vxmax, Vxmin;
    static float Vymax, Vymin;

    //c1和c2为学习因子
    static float c1, c2;

};


#endif //PSO_PARTICLE_H
