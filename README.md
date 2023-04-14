# GJK Collision Resolution
![](https://img.shields.io/badge/VisualStudio-%235D2B90.svg?style=flat&logo=visualstudio)  
![](https://img.shields.io/badge/-C++-blue)
![](https://img.shields.io/badge/-GLSL-pink?style=flat&logo=glsl)
![](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=flat&logo=opengl)
![](https://img.shields.io/badge/glm-yellow)
![](https://img.shields.io/badge/GLFW-orange)
![](https://img.shields.io/badge/GLEW-yellowgreen)


# Description
GJK Collision Resolution is a C++ project that implements the GJK collision detection algorithm based on [Winter’s blog article and tutorial](https://blog.winter.dev/2020/gjk-algorithm/). In the beginning this was meant to be part of the game engine written at the university but it wouldn’t work so here is a separate project implementing just that.

# Installation
For this project to work you have to download three libraries: 
[glm](https://github.com/g-truc/glm/releases/tag/0.9.9.8), 
[GLFW](https://www.glfw.org/) and 
[GLEW](https://glew.sourceforge.net/).  
Next they all have to be extracted into the *Dependencies* directory.  
[This video](https://www.youtube.com/watch?v=OR4fNpBjmq8&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=2) may help a lot.

# Usage
**Scene contents**:  
camera, two cubes, a simple pointlight.

**Steering**:  
User can move around with the camera using `mouse` and the `wsad` keys.
To move one cube around use `l.,/` keys.  
When colliding, cubes will become red.
