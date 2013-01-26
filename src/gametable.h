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
#include <vector>

#include "point.h"
#include "dimension.h"
#include "glcube.h"
#include "gametablelettercube.h"

namespace WordGL {
        
    class GameTable : public GLCube {

    public:
        GameTable(Point startPoint, Dimension dimension);
        virtual ~GameTable();
        void draw();
        bool isGameOver();
        void addNewLine();
        bool ifContainsCharactersRemove(std::vector<char> characters);
        char getRandomCharacter();
        void showGameOverScreen();
        void restart();
        
    private:
        GLfloat cubeUnit;
        GLfloat cubePadding;
        unsigned int columns;
        unsigned int rows;
        std::vector<GameTableLetterCube*> letterCubes;
        bool longerThanMaximum;
        
    };

}