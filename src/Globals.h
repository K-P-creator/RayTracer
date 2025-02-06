#ifndef GLOBALS_H
#define GLOBALS_H

//output image resolution
//my native res
#define SCENE_HEIGHT  1600
#define SCENE_WIDTH  2560

//constants for ambiant light and diffusion
#define SCENE_K_DIFF 0.6
#define SCENE_K_AMB 0.3

#define SCENE_LIGHT_SRC 1000, 10000, -800
#define SCENE_BACKGROUND 50,50,50

//spheres farther than this number from the origin will not be rendered
#define MAX_DISTANCE 200000 

#endif // GLOBALS_H