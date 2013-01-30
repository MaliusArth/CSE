/**
 *  WordGL
 *  Copyright (C) 2013  Viktor Was <viktor.was@technikum-wien.at>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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