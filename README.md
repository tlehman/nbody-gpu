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

```c
typedef struct body {
    float r; // radius
    float m; // mass
    float x,y,z;    // position
    float vx,vy,vz; // velocity
} body;
```

## Algorithms

To update the state of the universe, each unique pair of bodies needs to be selected to calculate it's mutual gravitational attraction. So with $n$ bodies, this runs at $O(n^2)$. 

We can pass in the $n$ bodies into GPU memory, and then divide the CUDA kernels up to compute the force vectors in parallel.
