#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "initial_conditions.h"

static int n = 2;
const float dt = 0.01;

// In this universe we use global variables
body * bodies;

void sig_handler(int signum) {
    printf("SIGNAL RECEIVED: %d\n", signum);
    printf("cleaning up.");
    free(bodies);
    exit(0);
}

void evolve_universe() {
    float mi, mj, rij;
    float xij, yij, zij;
    float f, fijx, fijy, fijz;
    // Calculate the total force on each body
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
                xij = bodies[j].x - bodies[i].x;
                yij = bodies[j].y - bodies[i].y;
                zij = bodies[j].z - bodies[i].z;
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
    }
    // Now all forces are calculated, now we update the positions and velocities

    float aix, aiy, aiz; 
    for(int i = 0; i < n; i++) {
        // F = ma implies a = F/m
        aix = bodies[i].fx / bodies[i].m;
        aiy = bodies[i].fy / bodies[i].m;
        aiz = bodies[i].fz / bodies[i].m;

        bodies[i].vx += aix * dt;
        bodies[i].vy += aiy * dt;
        bodies[i].vz += aiz * dt;

        bodies[i].x += bodies[i].vx * dt;
        bodies[i].y += bodies[i].vy * dt;
        bodies[i].z += bodies[i].vz * dt;

        printf(
            "(%0.3f, %0.3f, %0.3f), ", 
            bodies[i].fx,
            bodies[i].fy,
            bodies[i].fz
        );
    }
    printf("\n");
    glutPostRedisplay();
}

// display the state of the universe using OpenGL
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    float x,y,z,r;
    for(int i = 0; i < n; i++) {
        glPushMatrix();
        x = bodies[i].x;
        y = bodies[i].y;
        r = bodies[i].r;
        glTranslatef(x, y, 0);
        glutSolidSphere(r, 20, 16);
        glPopMatrix();
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    // -1: Allocate dynamic global variable. No I'm not sorry
    bodies = malloc(n * sizeof(body));
    memset(bodies, 0, n * sizeof(body)); // zero out all the things

    // 0. Handle system signals
    signal(SIGINT, sig_handler);

    // 1. Set up initial conditions for a binary star system
    initialize_binary_star(bodies, n);

    // 2. Initialize the OpenGL stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("n-body simulation");
    glClearColor(0.0, 0.0, 0.0, 0.0);


    // 3. Roll physics loop into graphics display loop
    glutDisplayFunc(display);
    glutIdleFunc(evolve_universe);
    glutMainLoop();

    free(bodies);
    return 0;
}