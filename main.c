#include <stdio.h>
#include <math.h>

typedef struct body {
    float r;        // radius
    float m;        // mass
    float x,y,z;    // position
    float vx,vy,vz; // velocity
} body;

const int G = 1.0; // setting all my constants 1 

const int n = 2;

void initialize_binary_star(body* bodies) {
    int m = 10;
    int r = 1.0;
    float v = sqrt((G * m)/(4 * r));
    bodies[0].x = 1.0;
    bodies[0].vy = v;

    bodies[1].x = -1.0;
    bodies[1].vy = -v;
}

int main() {
    // 1. Set up initial conditions for a binary star system
    body bodies[n];
    initialize_binary_star(bodies);

    // 2. Run physics loop
    return 0;
}