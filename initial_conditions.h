#include "types.h"

void initialize_binary_star(body *bodies, int n) {
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
