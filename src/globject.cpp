/**
 *  WordGL
 *  Copyright (C) 2012  Bernhard Posselt <bernhard.posselt@gmx.at>
 *  01.2013: Edited by Viktor Was <viktor.was@technikum-wien.at>
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
    
    /**
     * Constructor
     */
    GLObject::GLObject() {

    }
    
    /**
     * Sets the coords and the dimensions of the GLObject
     * @param startPoint The coord from which to start drawing
     * @param dimension The dimensions of the GLObject
     */
    void GLObject::setCoordsDimension ( Point startPoint, Dimension dimension ) {
        this->startX = startPoint.getXCoord();
        this->startY = startPoint.getYCoord();
        this->startZ = startPoint.getZCoord();
        this->width = dimension.getWidth();
        this->depth = dimension.getDepth();
        this->height = dimension.getHeight();
    }
    
    /**
     * Sets the color of the GLObject
     * @param color The color to apply to the GLObject
     */
    void GLObject::setColor ( Color color ) {
        _color = color;
    }
    
    /**
     * Sets the color of the GLObject
     * @param red Red channel of the color
     * @param green Green channel of the color
     * @param blue Blue channel of the color
     * @param alpha Alpha channel of the color defining transparency/translucency
     */
    void GLObject::setColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
        _color.r = red;
        _color.g = green;
        _color.b = blue;
        _color.a = alpha;
    }
    
    /**
     * Moves the GLObject
     * @param xCoord X coord of the vector to move by
     * @param yCoord Y coord of the vector to move by
     * @param zCoord Z coord of the vector to move by
     */
    void GLObject::move( GLfloat xCoord, GLfloat yCoord, GLfloat zCoord) {
        glTranslatef(xCoord, yCoord, zCoord);
    }

    /**
     * Returns the nearest point of the AABB according to the camera position
     * @return the nearest point of the AABB
     */
    Point GLObject::getNearest(Point point) {
        Point nearest = Point(
            (sqrt(pow(startX-point.getXCoord(), 2))<=sqrt(pow((startX+width)-point.getXCoord(), 2))?startX:startX+width),
            (sqrt(pow(startY-point.getYCoord(), 2))<=sqrt(pow((startY+height)-point.getYCoord(), 2))?startY:startY+height),
            (sqrt(pow(startZ-point.getZCoord(), 2))<=sqrt(pow((startZ+depth)-point.getZCoord(), 2))?startZ:startZ+depth));
        return nearest;
    }
    
    /**
     * Destructor
     */
    GLObject::~GLObject() {

    }

}