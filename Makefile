CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRC = src/Main.cpp src/Sphere.cpp src/Scene.cpp src/Plane.cpp
HEADERS = src/Sphere.h src/Scene.h src/Color.hpp src/Ray.hpp src/Globals.h src/Plane.h src/myVector.hpp src/Object.h
OUT = raytracer

all: $(OUT)

$(OUT): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT) output/*.ppm