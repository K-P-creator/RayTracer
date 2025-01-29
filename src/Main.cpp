// Demonstrates ray tracing functionality with multiple spheres and colors
// Outputs to a .ppm file, I use GIMP to display .ppm

#include "Scene.h" 
#include "Globals.h"

int main(void) {

    // Initialize spheres
    Sphere sphere1(200, Vector(600, 800, 500), Color(255, 0, 0));       // Red sphere
    Sphere sphere2(150, Vector(900, 800, 600), Color(0, 255, 0));       // Green sphere
    Sphere sphere3(300, Vector(400, 800, 700), Color(0, 0, 255));       // Blue sphere
    Sphere sphere4(100, Vector(700, 400, 300), Color(255, 255, 0));     // Yellow sphere closer to light
    Sphere sphere5(250, Vector(1000, 1000, 800), Color(0, 255, 255));   // Cyan sphere farther away
    Sphere sphere6(200, Vector(1500, 800, 300), Color(200, 0, 50));     // Dark red sphere
    Sphere sphere7(250, Vector(1800, 600, 400), Color(50, 200, 50));    // Light green sphere
    Sphere sphere8(300, Vector(2100, 1200, 500), Color(50, 50, 200));   // Light blue sphere
    Sphere sphere9(350, Vector(2400, 400, 600), Color(200, 200, 50));   // Yellowish-green sphere
    Sphere sphere10(400, Vector(2700, 200, 700), Color(200, 50, 200));  // Magenta sphere

    // Construct the scene with spheres
    Scene scene{ sphere1, sphere2, sphere3, sphere4, sphere5, sphere6, sphere7, sphere8, sphere9, sphere10 };

    // Set constants for the scene
    scene.set_background(Color(50, 50, 50));          // Dim gray background
    scene.set_k_diff(0.6);                            // Diffuse reflection coefficient
    scene.set_k_amb(0.3);                             // Ambient light coefficient
    scene.set_light_source(Vector(800, 200, 0));      // Light source above and to the side
    scene.set_height(SCENE_HEIGHT);                   // Output height (Full HD resolution)
    scene.set_width(SCENE_WIDTH);                     // Output width (Full HD resolution)
    scene.set_viewpoint(Vector(800, 800, -2000));     // Camera position looking at the scene

    // Draw the scene
    scene.draw();

    return 0;
}