# LJGL-EXAMPLE
## Compiling
OpenGL is the only package you need to worry about installing seperate to this git repo. As long as you clone recursively, GLM and GLFW will be included.


OpenGL is added to the build via `find_package(OpenGL REQUIRED)` in LJGL/CMakeLists.txt
```
git clone https://github.com/LJ3D/LJGL-EXAMPLE.git --recursive
mkdir LJGL-EXAMPLE/build && cd LJGL-EXAMPLE/build
cmake .. && cmake --build .
```
To run the program:
```
cd example/   # You have to run the example program from inside this dir
./example     # Run the example
# Now you can use wasd to move around; start with holding 's' to move out of the cube made up of Suzannes
```
