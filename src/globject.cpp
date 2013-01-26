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

#include "globject.h"
#include "textureloader.h"
#include <string>

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

namespace WordGL {

    GLObject::GLObject() {

    }

    void GLObject::setCoordsDimension ( Point startPoint, Dimension dimension ) {
        this->startX = startPoint.getXCoord();
        this->startY = startPoint.getYCoord();
        this->startZ = startPoint.getZCoord();
        this->width = dimension.getWidth();
        this->depth = dimension.getDepth();
        this->height = dimension.getHeight();
    }

    void GLObject::setColor ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
        glColor4f(red, green, blue, alpha);
    }

    void GLObject::move ( GLfloat xCoord, GLfloat yCoord, GLfloat zCoord) {
        glTranslatef(xCoord, yCoord, zCoord);
    }

    Point GLObject::getNearest(Point point) {
        Point nearest = Point(
            (sqrt(pow(startX-point.getXCoord(), 2))<=sqrt(pow((startX+width)-point.getXCoord(), 2))?startX:startX+width),
            (sqrt(pow(startY-point.getYCoord(), 2))<=sqrt(pow((startY+height)-point.getYCoord(), 2))?startY:startY+height),
            (sqrt(pow(startZ-point.getZCoord(), 2))<=sqrt(pow((startZ+depth)-point.getZCoord(), 2))?startZ:startZ+depth));
        return nearest;
    }
    
    GLObject::~GLObject() {

    }

}