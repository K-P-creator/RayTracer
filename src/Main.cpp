// Demonstrates ray tracing functionality with multiple objs and colors
// Outputs to a .ppm file, I use GIMP to display .ppm

//usage ./raytracer -debug(optional) -bench(optional)

#include "Plane.h"
#include "Sphere.h"
#include "Scene.h"
#include "Globals.h"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <memory>

using namespace std;

namespace globals{
    bool debug = false;
    bool bench = false;
}

//returns random double in range [min, max]
double randomDouble(double min, double max);

//executes thread benchmark draw()
void benchmarkDraw(Scene & scene);

void parseArgs(int, char**);

int main(int argc, char** argv) {
    //parse command line args
    parseArgs(argc, argv);

    //set size ranges
    vector<shared_ptr<Object>> objs;
    int numobjs = 50;
    double minRadius = 150, maxRadius = 700;


    // Generate spheres with random attributes
    if (globals::debug) cout << endl << "Randomizing Objects..." << endl;
    
    //seed
    srand(static_cast<unsigned int>(time(nullptr)));

    //generate sphere objects
    if (globals::debug) cout << "Generating Spheres..." << endl;
    for (int i = 0; i < numobjs; i++) {
        double radius = randomDouble(minRadius, maxRadius);
        bool collide = true;
        myVector position;
        while (collide && objs.size() != 0){
            position = myVector(
                randomDouble(-8000, SCENE_WIDTH + 8000),   // X position
                randomDouble(50, SCENE_HEIGHT + 800),  // Y position
                randomDouble(1000, 17000)    // Z position
            );
            collide = Scene(objs).checkSphereCollision(Sphere(radius, position, Color(1,1,1)));
        }

        Color color(
            static_cast<int>(randomDouble(50, 255)),  // Red
            static_cast<int>(randomDouble(50, 255)),  // Green
            static_cast<int>(randomDouble(50, 255))   // Blue
        );

        objs.emplace_back(make_shared<Sphere>(radius, position, color));
    }

    //create a floor plane and add it to objs 
    if (globals::debug) cout << "Generating Plane..." << endl;
    objs.emplace_back(make_shared<Plane>(myVector(0.0, 0.0, 1.0), myVector(0, 1, 0), Color(255,10,10)));


    // Create scene with the generated objs
    if (globals::debug) cout << "Constructing Scene..." << endl;
    Scene scene(objs);

    if (globals::debug) cout << "Setting Constants..." << endl;

    // Set constants for the scene
    scene.set_background(Color(SCENE_BACKGROUND));          // Dim gray background
    scene.set_k_diff(SCENE_K_DIFF);                            // Diffuse reflection coefficient
    scene.set_k_amb(SCENE_K_AMB);                             // Ambient light coefficient
    scene.set_light_source(myVector(SCENE_LIGHT_SRC));      // Light source 
    scene.set_height(SCENE_HEIGHT);                   // Output height
    scene.set_width(SCENE_WIDTH);                     // Output width
    scene.set_viewpoint(myVector(800, 800, -2000));     // Camera position looking at the scene


    //draw the scene
    if (globals::debug) cout << "Drawing Scene..." << endl;

    if (globals::bench){
        if (globals::debug) cout << "Starting Benchmark Draws..." << endl;
        benchmarkDraw(scene);
    }else{
        if (globals::debug) cout << "Starting MultiThreaded Draw..." << endl;
        scene.multiThreadedDraw();
    }

    if (globals::debug) cout << "Done!" << endl;
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

void parseArgs(int argc, char** argv){
    for (int i = 1; i < argc; i ++){
        if (string(argv[i]) == "-bench") globals::bench = true;
        if (string(argv[i]) == "-debug") globals::debug = true;
    }
}