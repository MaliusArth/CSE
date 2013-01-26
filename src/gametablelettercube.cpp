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

/**
 * This class represents a lettercube which is on the gametable. We have to
 * store columns and rows additionally
 */

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "gametablelettercube.h"
#include "lettercube.h"
#include "point.h"
#include "dimension.h"

namespace WordGL {
    
    /**
     * @param startPoint the startPoint where the object should be drawn
     * @param dimension the dimesions of the object
     * @param letter the texture id for the top
     * @param cubeUnit the width and depth
     */
    GameTableLetterCube::GameTableLetterCube(Point startPoint, Dimension dimension, char letter, GLfloat cubeUnit):
        LetterCube(startPoint, dimension, letter){
        this->column = 0;
        this->row = 0;
        this->cubeUnit = cubeUnit;
    }
    
    /**
     * Returns the current colum of the block that it is in
     * @return its current column
     */
    unsigned int GameTableLetterCube::getColumn() {
        return this->column;
    }
    
    /**
     * Returns the current row of the block that it is in
     * @return its current row
     */
    unsigned int GameTableLetterCube::getRow() {
        return this->row;
    }
    
    /**
     * Mark the cubes row as one more down the gametable
     */
    void GameTableLetterCube::incrementRow() {
        this->row += 1;
        this->startZ += this->cubeUnit;
    }

    /*void GameTableLetterCube::draw() {
        LetterCube::draw();
    }*/
    
    GameTableLetterCube::~GameTableLetterCube() {
        
    }
    
}