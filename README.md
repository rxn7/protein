# Protein
Protein is a 3D game framework based on modern OpenGL written in C.  
Note: This was one of my first C projects... 

# Using
## Linking
* Get a libprotein.a from latest release or compile it from source (see [Compiling](#compiling))
* Link your program with ``` -lGLEW -lglfw -lGL ```

## Depedencies
* GLEW
* GLFW

# Development
## Compiling
To compile Protein run ```./build.sh```.  
<br>
You can compile Protein and an example from examples folder using ```./build.sh <example name>```.

E.g.: ```./build.sh sandbox``` will compile Protein and sandbox example. It will also run the sandbox example after it's done compiling.

## Depedencies
* gcc
* make
* GLEW
* GLFW
* Valgrind (optional, for debugging)
