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


#pragma once

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "lettercube.h"
#include "dimension.h"
#include "point.h"


namespace WordGL {
    
    class GameTableLetterCube: public LetterCube {
    public:
        GameTableLetterCube(Point startPoint, Dimension dimension, char letter, GLfloat cubeUnit);
        virtual ~GameTableLetterCube(void);
        unsigned int getColumn(void);
        unsigned int getRow(void);
        void incrementRow(void);
        //virtual void draw(void);
        
    private:
        int column;
        int row;
        GLfloat cubeUnit;
    };
    
}
    
