// Demonstrates ray tracing functionality with multiple spheres and colors
// Outputs to a .ppm file, I use GIMP to display .ppm

//usage ./raytracer [benchmark mode: T (optional)]

#include "Scene.h"
#include "Globals.h"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

//returns random double in range [min, max]
double randomDouble(double min, double max);

//executes thread benchmark draw()
void benchmarkDraw(Scene & scene);

int main(int argc, char** argv) {
    
    //set size ranges
    std::vector<Sphere> spheres;
    int numSpheres = 100;
    double minRadius = 15, maxRadius = 200;


    // Generate spheres with random attributes
    cout << "Randomizing Spheres..." << endl;

    //seed
    srand(static_cast<unsigned int>(time(nullptr)));

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
    cout << "Constructing Scene" << endl;
    Scene scene(spheres);

    // Set constants for the scene
    scene.set_background(Color(50, 50, 50));          // Dim gray background
    scene.set_k_diff(0.6);                            // Diffuse reflection coefficient
    scene.set_k_amb(0.3);                             // Ambient light coefficient
    scene.set_light_source(myVector(400, 100, -2000));      // Light source above and to the side
    scene.set_height(SCENE_HEIGHT);                   // Output height (Full HD resolution)
    scene.set_width(SCENE_WIDTH);                     // Output width (Full HD resolution)
    scene.set_viewpoint(myVector(800, 800, -2000));     // Camera position looking at the scene


    //draw the scene
    cout << "Drawing Scene..." << endl;

    if (argc != 1){
        if (*argv[1] == 'T') benchmarkDraw(scene);
    }else{
        scene.multiThreadedDraw();
    }

    cout << "Done!" << endl;
    return 0;
}

//returns random double in range [min, max]
double randomDouble(double min, double max){
    //grab a randon double
    double rand = static_cast<float>(std::rand()) / RAND_MAX;

    //set range [min, max]
    return min + rand * (max - min);
}

//executes thread benchmark draw()
void benchmarkDraw(Scene & scene){
    //timed executions output to the console
    cout << "Starting single thread execution..." << endl;
    auto startSingle = chrono::high_resolution_clock::now();

    scene.draw();

    auto endSingle = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSingle = endSingle - startSingle;

    cout << "Elapsed time: " << elapsedSingle.count() << " seconds\n";
    
    // Draw the scene multi thread
    cout << "Starting multi-threaded execution..." << endl;
    auto startMult = chrono::high_resolution_clock::now();

    scene.multiThreadedDraw();

    auto endMult = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedMult = endMult - startMult;

    cout << "Elapsed time: " << elapsedMult.count() << " seconds\n";
}