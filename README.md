# $n$-body physics simulation with gpu acceleration
by @tlehman

## Assumptions (in the matrix)
- Euclidean space (no curvature)
- Newtonian gravity is the only force
- All bodies are spheres

## Assumptions (in the real world)
- Existence of an NVIDIA GPU
- Computer runs Linux
- OpenGL is present (TODO)

## The equations of motion

Each of the $n$ bodies will have a mass $m$ and a position $x(t)$ that is a 3-vector like $(0.1, -0.2, 3.1)$

The bodies need to be initialized with:

- masses
- positions and 
- velocities

Once initialized, the simulation loop will take over.

## Data structures

The state of the universe is an array of length $n$, each cell of the array is the state of a body:

```c++
struct body {
    float radius;      // radius
    float x,y,z;       // position
    float vx, vy, vz;  // velocity
    float m;           // mass
};
```
