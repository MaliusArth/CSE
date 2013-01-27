/**
 *  WordGL
 *  Copyright (C) 2012  Bernhard Posselt <bernhard.posselt@gmx.at>
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


#pragma once

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "point.h"
#include "dimension.h"
#include "textureloader.h"

namespace WordGL {
    
    struct Color
    {
        Color(GLfloat red = 1.0f, GLfloat green = 1.0f, GLfloat blue = 1.0f, GLfloat alpha = 1.0f){
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
        GLfloat r,g,b,a;
    };

    class GLObject {

    public:
        GLObject();
        virtual ~GLObject();
        void setColor(Color color);
        void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
        virtual Point getNearest(Point point);

    protected:
        void setCoordsDimension(Point startPoint, Dimension dimension);
        void move(GLfloat xCoord, GLfloat yCoord, GLfloat zCoord);
        GLfloat startX, startY, startZ;
        GLfloat width, height, depth;
        Color _color;

    };

}