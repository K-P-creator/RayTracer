// Demonstrates ray tracing functionality with multiple spheres and colors
// Outputs to a .ppm file, I use GIMP to display .ppm

#include "Scene.h"
#include "Globals.h"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

// Function to generate a random float within a range
double randomDouble(double min, double max) {
    std::random_device rd;  // Non-deterministic random source
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

int main() {
    std::vector<Sphere> spheres;
    int numSpheres = 80;

    double minRadius = 50, maxRadius = 300;   // Sphere size range

    // Generate spheres with random attributes
    for (int i = 0; i < numSpheres; i++) {
        double radius = randomDouble(minRadius, maxRadius);
        myVector position(
            randomDouble(-500, SCENE_WIDTH + 500),   // X position
            randomDouble(-300, SCENE_HEIGHT + 300),  // Y position
            randomDouble(0, 1000)    // Z position
        );

        Color color(
            static_cast<int>(randomDouble(50, 255)),  // Red
            static_cast<int>(randomDouble(50, 255)),  // Green
            static_cast<int>(randomDouble(50, 255))   // Blue
        );

        spheres.emplace_back(radius, position, color);
    }

    // Create scene with the generated spheres
    Scene scene(spheres);

    // Set constants for the scene
    scene.set_background(Color(50, 50, 50));          // Dim gray background
    scene.set_k_diff(0.6);                            // Diffuse reflection coefficient
    scene.set_k_amb(0.3);                             // Ambient light coefficient
    scene.set_light_source(myVector(400, 100, -2000));      // Light source above and to the side
    scene.set_height(SCENE_HEIGHT);                   // Output height (Full HD resolution)
    scene.set_width(SCENE_WIDTH);                     // Output width (Full HD resolution)
    scene.set_viewpoint(myVector(800, 800, -2000));     // Camera position looking at the scene

    //timed executions output to the console
    cout << "Starting single thread execution..." << endl;
    auto startSingle = chrono::high_resolution_clock::now();

    scene.draw();

    auto endSingle = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSingle = endSingle - startSingle;

    cout << "Elapsed time: " << elapsedSingle.count() << " seconds\n";
    
    // Draw the scene
    cout << "Starting multi-threaded execution..." << endl;
    auto startMult = chrono::high_resolution_clock::now();

    scene.multiThreadedDraw();

    auto endMult = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedMult = endMult - startMult;

    cout << "Elapsed time: " << elapsedMult.count() << " seconds\n";

    return 0;
}