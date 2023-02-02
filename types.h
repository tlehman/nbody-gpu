const float G = 1.0; // not a type, but a const

typedef struct body {
    float r;        // radius
    float m;        // mass
    float x,y,z;    // position
    float vx,vy,vz; // velocity
    float fx,fy,fz; // force on object (added up each sim loop)
} body;

