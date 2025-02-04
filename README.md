Simple Ray Tracer that outputs a .ppm file to display results

I have implemented multi-threading to greatly speed up the render time of a scene.
Default scene res is 2560x1600 (my native res, you can change this in globals.h)
and the main generates 100 random spheres to render. It also includes a timer to 
compare the single vs multi threaded render times. My most recent run with the updated 
globals/main is as follows:

Starting single thread execution...
Elapsed time: 13.1985 seconds
Starting multi-threaded execution...
Elapsed time: 2.85339 seconds

This represents a 4.6X boost in Speed!

I use GIMP to view .ppm files. If you don't have GIMP, I included a screenshot of out.ppm
saved as output/out-example. This ray tracer currently only supports sphere objects. 
Included are custom Color, Ray, Vector, Sphere and Scene classes. I port to the SFML library 
in the future to display results rather than depending on the .ppm. I also want to implement
more performance enhancing tecniques such as SIMD and better workload distribution for the
threads. Perhaps eventually I will work on rendering with GPU instead of CPU as well.

Compiles with G++ (tested on windows)
Use:
make -f Makefile.txt
./raytracer

