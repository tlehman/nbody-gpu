#include "types.h"
#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

static int n = 3844;
const float dt = 0.0001;

void init_binary_star(body *bodies, int n) {
    assert(n == 2);
    float m = 10.0;
    float r = 0.1;
    float d = 1.0;
    float v = sqrt((G * m)/(4 * d));
    // Set mass and radius
    bodies[0].m = m;
    bodies[0].r = r;
    bodies[1].m = m;
    bodies[1].r = r;

    // Set positions
    bodies[0].x = d;
    bodies[1].x = -d;

    // Set the velocities
    bodies[0].vy = v;
    bodies[1].vy = -v;
}

// The 3-body orbit in the shape of a figure-eight
// See https://tobilehman.com/pdf/ooo.pdf (page 43) for more details
void init_figure_eight(body *bodies, int n) {
    assert(n == 3);
    float m = 1.0;
    float r = 0.05;
    float d = 1.0;
    for(int i = 0; i < n; i++) {
        bodies[i].m = m;
        bodies[i].r = r;
    }

    // Set the positions
    bodies[0].x = 0.97000436;
    bodies[0].y = -0.24308753;

    bodies[1].x = -bodies[0].x;
    bodies[1].y = -bodies[0].y;

    // Set the velocites
    bodies[2].vx = -0.93240737;
    bodies[2].vy = -0.86473146;

    bodies[0].vx = -0.5 * bodies[2].vx;
    bodies[0].vy = -0.5 * bodies[2].vy;

    bodies[1].vx = -0.5 * bodies[2].vx;
    bodies[1].vy = -0.5 * bodies[2].vy;
}

float frand() {
    return (rand() & 10)/10.0;
}

void init_random(body *bodies, int n) {
    srand(time(0)); // seed the PRNG
    float offset = 0.5;
    for(int i = 0; i < n; i++) {
        bodies[i].r = frand()/20;
        bodies[i].m = bodies[i].r;
        bodies[i].x = frand() - offset;
        bodies[i].y = frand() - offset;
        bodies[i].z = frand() - offset;
        bodies[i].vx = frand() - offset;
        bodies[i].vy = frand() - offset;
        bodies[i].vz = frand() - offset;
    }
}

float g(body * a, body * b) {
    float r = sqrt(
        (a->x - b->x)*(a->x - b->x) +
        (a->y - b->y)*(a->y - b->y) +
        (a->z - b->z)*(a->z - b->z)
    );
    return (G * a->m * b->m) / (r * r);
}

// sun at the middle, and two planets, one with a moon, and another with two
// 0. unixstar 
// 1. tux
// 2. tuxmoongeeko (Geeko the SUSE Chamelion (sorry lizards, the name is what it is))
//
// 3. beastie   (the FreeBSD mascot)
// 4. dragonfly (for DragonFlyBSD)
// 5. blowfish  (blowfish, the OpenBSD mascot)
void init_star_system(body* bodies, int n) {
    //assert(n == 6);
    assert(n == 3);
    body *unixstar     = &bodies[0];
    body *tux          = &bodies[1];
    body *tuxmoongeeko = &bodies[2];
    body *beastie      = &bodies[3];
    body *dragonfly    = &bodies[4];
    //body *blowfish     = bodies[5];

    unixstar->m = 333000; // ratio of sun mass to earth
    unixstar->r = 0.2;
    tux->m = 1;
    tux->r = 0.005;
    tuxmoongeeko->m = 0.00001; // ratio of earth mass to the moon
    tuxmoongeeko->r = 0.002;
    // to calculate the stable circular orbit, a=v²/r, so set a = g, the gravitational force 
    // v=⎷(rg)
    float rtux = 0.5;
    tux->x = rtux;
    tux->vy = sqrt(rtux * g(unixstar, tux));

    float rsuse = rtux/64.2;
    tuxmoongeeko->x = rtux + rsuse;
    tuxmoongeeko->vy = 1.03376*tux->vy;
}

bool perfect_square(int n) {
    if(n < 1) { return false; }
    float root = sqrt(n);
    return floor(root) == root;
}

void init_grid(body* bodies, int n) {
    assert(perfect_square(n));
    int root = sqrt(n);
    for(int i = 0; i < root; i++) {
        for(int j = 0; j < root; j++) {
            body * b = &bodies[i * root + j];
            b->m = 1.0 +  i*j/10000.0;;
            b->r = 0.01 + i*j/100000.0;
            b->vx = i-100;
            b->vy = j;
            b->x = i/10.0;
            b->y = j/10.0;
        }
    }
    bodies[0].x = -0.2;
    bodies[0].y = -0.2;
    bodies[0].vx = 0;
    bodies[0].vy = 0;
    bodies[0].m = 10000;
    bodies[0].r = 0.2;
}