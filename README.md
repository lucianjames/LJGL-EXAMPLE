# LJGL-EXAMPLE
## Compiling
OpenGL is the only package you need to worry about installing seperate to this git repo. As long as you clone recursively, GLM and GLFW will be included.


OpenGL is added to the build via `find_package(OpenGL REQUIRED)` in LJGL/CMakeLists.txt
```
git clone https://github.com/LJ3D/LJGL-EXAMPLE.git --recursive
mkdir LJGL-EXAMPLE/build && cd LJGL-EXAMPLE/build
cmake .. && cmake --build .
```
