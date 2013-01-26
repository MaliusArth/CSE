/**
 *  WordGL
 *  Copyright (C) 2012  Patrick Stapfer <p.stapfer@technikum-wien.at>
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

/**
 * Represents a cube with a header texture
 */

#include <string>

//#include "glcube.h"
#include "window.h"
#include "lettercube.h"
#include "settings.h"

namespace WordGL {
    
    /**
     * @param startPoint the startPoint where the object should be drawn
     * @param dimension the dimesions of the object
     * @param letter the texture id for the top
     */
    LetterCube::LetterCube (Point startPoint, Dimension dimension, char letter): GLCube(startPoint,dimension) {
        this->setLetter(letter);
    }
    
    /**
     * Returns the letter from the header texture
     * @return the letter which was set
     */
    char LetterCube::getLetter(){
        return this->letter;
    }
    
    /**
     * sets a letter for the header texture
     */
    void LetterCube::setLetter(char letter){
        this->letter = letter;
        std::string textureName("");
        textureName += this->letter;
        this->setTopTexture(textureName);
        std::string standardTexture("tile");
        this->setBottomTexture(standardTexture);
        this->setFrontTexture(standardTexture);
        this->setBackTexture(standardTexture);
        this->setLeftTexture(standardTexture);
        this->setRightTexture(standardTexture);
    }
    void LetterCube::draw() {
        glPushMatrix();
        Point nearest = getNearest(Point(Window::getInstance()->camera_pos[0], Window::getInstance()->camera_pos[1],Window::getInstance()->camera_pos[2]));
        //std::cout << "TexName: " << this->topTextureName << " eyeX: " << Window::getInstance()->eyeX << " eyeY: " << Window::getInstance()->eyeY << " eyeZ: " << Window::getInstance()->eyeZ << std::endl;
        GLfloat distance = sqrt(pow(Window::getInstance()->camera_pos[0]-nearest.getXCoord(), 2)+pow(Window::getInstance()->camera_pos[1]-nearest.getYCoord(), 2)+pow(Window::getInstance()->camera_pos[2]-nearest.getZCoord(), 2));

        if( distance >= LOD_RANGE_3 )
        {
            this->setColor(1.0f, 0.0f, 0.0f);
        }
        else if( distance >= LOD_RANGE_2 )
        {
            this->setColor(0.0f, 1.0f, 0.0f);
        }
        else if( distance >= LOD_RANGE_1 )
        {
            this->setColor(0.0f, 0.0f, 1.0f);
        }
        else
            colorLocked = false;
        
        GLCube::draw();

        glPopMatrix();
    }
    
    Point LetterCube::getNearest(Point point) {
        return GLCube::getNearest(point);
        /*GLfloat matrix[16]; 
        glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
        const float worldPosX = matrix[12];
        const float worldPosY = matrix[13];
        const float worldPosZ = matrix[14];

        Point nearest = Point(
            (sqrt(pow(worldPosX-point.getXCoord(), 2))<=sqrt(pow((worldPosX+width)-point.getXCoord(), 2))?worldPosX:worldPosX+width),
            (sqrt(pow(worldPosY-point.getYCoord(), 2))<=sqrt(pow((worldPosY+height)-point.getYCoord(), 2))?worldPosY:worldPosY+height),
            (sqrt(pow(worldPosZ-point.getZCoord(), 2))<=sqrt(pow((worldPosZ+depth)-point.getZCoord(), 2))?worldPosZ:worldPosZ+depth));
        return nearest;*/
    }

    LetterCube::~LetterCube() {
        
    }
    
}