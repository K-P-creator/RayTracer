Simple Ray Tracer that outputs a .ppm file to display results

I use GIMP to view .ppm files. This ray tracer currently only supports sphere objects. 
Included are custom Color, Ray, Vector, Sphere and Scene classes. I plan to add support
for multi threading in the future and also to implement the SFML library to display
results rather than depending on the .ppm. 

Compiles with G++ (tested on windows)
Use:
make -f Makefile.txt

Expect to see a branch soon with multi-threading
