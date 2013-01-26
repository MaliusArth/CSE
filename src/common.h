#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#ifdef WIN32
    #include <Windows.h>
#endif

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include <cstdlib>

#endif /* COMMON_H_INCLUDED */