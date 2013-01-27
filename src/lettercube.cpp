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

//#include "common.h"
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
        textureName = this->letter;
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

        if (Window::getInstance()->LODSwitch)
        {
            Point camera = Point(Window::getInstance()->camera_pos[0], Window::getInstance()->camera_pos[1], Window::getInstance()->camera_pos[2]);
            Point nearest = getNearest(camera);
            GLfloat distance = sqrt(pow(camera.getXCoord()-nearest.getXCoord(), 2)+pow(camera.getYCoord()-nearest.getYCoord(), 2)+pow(camera.getZCoord()-nearest.getZCoord(), 2));

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
            {
                this->setColor(1.0f, 1.0f, 1.0f);
            }
        }
        else
        {
            this->setColor(1.0f, 1.0f, 1.0f);
        }

        GLCube::draw();

        glPopMatrix();
    }
    
    Point LetterCube::getNearest(Point point) {
        return GLCube::getNearest(point);

        /*const float worldPosX = -(mdl[0] * mdl[12] + mdl[1] * mdl[13] + mdl[2] * mdl[14]);
        const float worldPosY = -(mdl[4] * mdl[12] + mdl[5] * mdl[13] + mdl[6] * mdl[14]);
        const float worldPosZ = -(mdl[8] * mdl[12] + mdl[9] * mdl[13] + mdl[10] * mdl[14]);*/

        /*glPushMatrix();
            glutSolidCube(0.5f);
        glPopMatrix();*/

        /*Point nearest = Point(
            (sqrt(pow(worldPosX-point.getXCoord(), 2))<=sqrt(pow((worldPosX+width)-point.getXCoord(), 2))?worldPosX:worldPosX+width),
            (sqrt(pow(worldPosY-point.getYCoord(), 2))<=sqrt(pow((worldPosY+height)-point.getYCoord(), 2))?worldPosY:worldPosY+height),
            (sqrt(pow(worldPosZ-point.getZCoord(), 2))<=sqrt(pow((worldPosZ+depth)-point.getZCoord(), 2))?worldPosZ:worldPosZ+depth));
        return nearest;*/
    }

    LetterCube::~LetterCube() {
        
    }
    
}