#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct body {
    float r;        // radius
    float m;        // mass
    float x,y,z;    // position
    float vx,vy,vz; // velocity
    float fx,fy,fz; // force on object (added up each sim loop)
} body;

const int G = 1.0;
const int n = 3;
const float dt = 0.0001;

void sig_handler(int signum) {
    printf("SIGNAL RECEIVED: %d\n", signum);
    printf("cleaning up.");
    exit(0);
}

void initialize_binary_star(body* bodies) {
    int m = 10;
    int r = 1.0;
    float v = sqrt((G * m)/(4 * r));
    // Set mass and radius
    bodies[0].m = m;
    bodies[0].r = r;
    bodies[1].m = m;
    bodies[1].r = r;

    // Set positions
    bodies[0].x = 1.0;
    bodies[0].y = 0;
    bodies[0].z = 0;

    bodies[1].x = -1.0;
    bodies[1].y = 0;
    bodies[1].z = 0;

    // Set the velocities
    bodies[0].vx = 0;
    bodies[0].vy = v;
    bodies[0].vz = 0;

    bodies[1].vx = 0;
    bodies[1].vy = -v;
    bodies[1].vz = 0;

    // Zero out the forces
    bodies[0].fx = 0;
    bodies[0].fy = 0;
    bodies[0].fz = 0;

    bodies[1].fx = 0;
    bodies[1].fy = 0;
    bodies[1].fz = 0;
}

void evolve_universe(body* bodies) {
    float mi, mj, rij;
    float xij, yij, zij;
    float f, fijx, fijy, fijz;
    for(int i = 0; i < n; i++) {
        // zero out force on object
        bodies[i].fx = 0.0;
        bodies[i].fy = 0.0;
        bodies[i].fz = 0.0;
        // loop over all other bodies in the universe
        for(int j = 0; j < n; j++) {
            if (i != j) {
                // compute the force between body i and j
                mi = bodies[i].m;
                mj = bodies[j].m;
                xij = bodies[i].x - bodies[j].x;
                yij = bodies[i].y - bodies[j].y;
                zij = bodies[i].z - bodies[j].z;
                rij = sqrt(
                    (xij * xij) +
                    (yij * yij) +
                    (zij * zij)
                );
                // F_ij is the magnitude of the force, now we need the direction
                f = (G * mi * mj)/(rij * rij);
                
                bodies[i].fx += f * xij/rij; // x component of force vector F_ij
                bodies[i].fy += f * yij/rij; // y component of force vector F_ij
                bodies[i].fz += f * zij/rij; // z component of force vector F_ij

            }
        }
        printf("bodies[%d].x = %3.f ", i, bodies[i].x);
    }
    printf("\n");
}

int main() {
    // 0. Handle system signals
    signal(SIGINT, sig_handler);

    // 1. Set up initial conditions for a binary star system
    body bodies[n];
    initialize_binary_star(bodies);

    // 2. Run physics loop
    while(1) {
        evolve_universe(bodies);
    }

    return 0;
}