// Demonstrates ray tracing functionality with multiple spheres and colors
// Outputs to a .ppm file, I use GIMP to display .ppm

#include "Scene.h" 

int main(void) {

    // Initialize spheres with overlapping shadows
    Sphere sphere1(200, Vector(600, 800, 500), Color(255, 0, 0));    // Red sphere
    Sphere sphere2(150, Vector(900, 800, 600), Color(0, 255, 0));    // Green sphere
    Sphere sphere3(300, Vector(400, 800, 700), Color(0, 0, 255));    // Blue sphere
    Sphere sphere4(100, Vector(700, 400, 300), Color(255, 255, 0));  // Yellow sphere closer to light
    Sphere sphere5(250, Vector(1000, 1000, 800), Color(0, 255, 255));// Cyan sphere farther away

    // Construct the scene with spheres
    Scene scene{ sphere1, sphere2, sphere3, sphere4, sphere5 };

    // Set constants for the scene
    scene.set_background(Color(50, 50, 50));          // Dim gray background
    scene.set_k_diff(0.6);                            // Diffuse reflection coefficient
    scene.set_k_amb(0.3);                             // Ambient light coefficient
    scene.set_light_source(Vector(800, 200, 0));      // Light source above and to the side
    scene.set_height(1080);                           // Output height (Full HD resolution)
    scene.set_width(1920);                            // Output width (Full HD resolution)
    scene.set_viewpoint(Vector(800, 800, -2000));     // Camera position looking at the scene

    // Draw the scene
    scene.draw();

    return 0;
}