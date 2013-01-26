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

#include "common.h"

#include "game.h"
//#include "textureloader.h"

namespace WordGL {
    
    class Window {

    public:
        Window(int* argc, char** argv, const char* title, int width, int height);
        ~Window();
        void init();
        void resize ( int width, int height );
        void keyPressed(unsigned char key, int x, int y);
        void display();
        void redisplayTimer(int value);
        static Window* getInstance();
		void specialKeyPressed(int key, int x, int y);
        
        // Camera
        GLfloat eyeX;
		GLfloat eyeY;
		GLfloat eyeZ;
        GLfloat camera_pos[3];

    private:
        int window;
        int width;
        int height;
        int windowRefreshRate;
        int windowRefreshInterval;
		
		GLfloat centerX;
		GLfloat centerY;
		GLfloat centerZ;
		GLfloat angle;
        const char* title;
        Game game;
        static Window* windowInstance;

        bool lightSwitch, LODSwitch;
        GLfloat LightAmbient[4];
        GLfloat LightDiffuse[4];
        GLfloat LightPosition[4];

        //GLfloat SpotLightPosition[4];
        //GLfloat SpotLightDirection[3];
    };

}