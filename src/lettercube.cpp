/**
 *  WordGL
 *  Copyright (C) 2012  Patrick Stapfer <p.stapfer@technikum-wien.at>
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
     * Sets a letter for the header texture
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

    /**
     * Draws the LetterCube
     */
    void LetterCube::draw() {
        glPushMatrix();
        
        glEnable(GL_BLEND); //Enable alpha blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function
        
        if (Window::getInstance()->LODSwitch)
        {
            Point camera = Point(Window::getInstance()->camera_pos[0], Window::getInstance()->camera_pos[1], Window::getInstance()->camera_pos[2]);
            Point nearest = getNearest(camera);
            GLfloat distance = sqrt(pow(camera.getXCoord()-nearest.getXCoord(), 2)+pow(camera.getYCoord()-nearest.getYCoord(), 2)+pow(camera.getZCoord()-nearest.getZCoord(), 2));

            if( distance >= LOD_RANGE_3 )
            {
                this->setColor(1.0f, 0.0f, 0.0f, 0.5f);
            }
            else if( distance >= LOD_RANGE_2 )
            {
                this->setColor(0.0f, 1.0f, 0.0f, 0.5f);
            }
            else if( distance >= LOD_RANGE_1 )
            {
                this->setColor(0.0f, 0.0f, 1.0f, 0.5f);
            }
            else
            {
                this->setColor(1.0f, 1.0f, 1.0f, 0.5f);
            }
        }
        else
        {
            this->setColor(1.0f, 1.0f, 1.0f, 0.5f);
        }

        GLCube::draw();
        glDisable(GL_BLEND);
        glPopMatrix();
    }

    /**
     * Destructor
     */
    LetterCube::~LetterCube() {
        
    }
    
}