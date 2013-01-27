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
 * This class is responsible for setting up opengl and initializing the game,
 * passing input to it and tell it to update
 */

#include "window.h"

#ifndef WIN32
    #include <unistd.h>
#endif

//#include <cstdlib>
#include <iostream>
#include <cmath>

#include "game.h"
#include "wrappers.h"
#include "settings.h"


namespace WordGL {
    
    // needed singleton for wrappers
    Window* Window::windowInstance = NULL;
    
    /**
    * Creates the window
    * @param title The window title
    * @param width The width of the window
    * @param height The height of the window
    */
    Window::Window (int* argc, char** argv, const char* title, int width, int height)
        : game(LINE_UPDATE_INTERVAL)
    {
        Window::windowInstance = this;
        this->title = title;
        // prevent division by 0
        if(height == 0){
            this->height = 1;
        } else {
            this->height = height;
        }
        this->width = width;
		this->eyeX = 3.0f;
		this->eyeY = 13.0f;
		this->eyeZ = 7.0f;
		this->centerX = 3.0f;
		this->centerY = 0.0f;
		this->centerZ = -6.0f;
        this->angle = 0.0f;
        glutInit(argc, argv);
    }

    /**
    * Initializes the window
    */
    void Window::init(){
        // initial opengl code
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
        glutInitWindowSize(this->width, this->height);
        glutInitWindowPosition(0, 0);
        this->window = glutCreateWindow(this->title);
        
        // initialize rendering

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        //glEnable(GL_COLOR_MATERIAL);
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        //Setup Lighting
        glEnable(GL_NORMALIZE);

        LightAmbient[0] = 0.3f; LightAmbient[1] = 0.3f; LightAmbient[2] = 0.3f; LightAmbient[3] = 1.0f;
        LightDiffuse[0] = 0.8f; LightDiffuse[1] = 0.8f; LightDiffuse[2] = 0.8f; LightDiffuse[3] = 1.0f;
        LightPosition[0] = 3.0f; LightPosition[1] = 3.0f; LightPosition[2] = 7.0f; LightPosition[3] = 1.0f;

        // Spotlight not visible...? [http://www.vbforums.com/showthread.php?416780-RESOLVED-Problems-with-Specular-light-and-Spotlight-in-OpenGL]
        //SpotLightPosition[0] = 3.0f; SpotLightPosition[1] = 5.0f; SpotLightPosition[2] = -6.0f; SpotLightPosition[3] = 1.0f;
        //SpotLightDirection[0] = 0.0f; SpotLightDirection[1] = -1.0f; SpotLightDirection[2] = 0.0f;

        glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);         // Setup The Ambient Light
        glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);         // Setup The Diffuse Light
        glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);        // Position The Light

        //glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, 15.f);             // Spotlight
        ////glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
        //glLightfv(GL_LIGHT2, GL_POSITION,SpotLightPosition);
        //glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotLightDirection);

        glEnable(GL_LIGHT1);
        //glEnable(GL_LIGHT2);
        
        lightSwitch = true;
        LODSwitch = false;
        //glEnable(GL_LIGHTING);      // Enable Lighting

        glEnable(GL_COLOR_MATERIAL);      // Enable Color Material
        glColorMaterial(GL_FRONT, GL_DIFFUSE);


        // get window refresh rate and interval
        this->windowRefreshRate = glutGameModeGet(GLUT_GAME_MODE_REFRESH_RATE);
        if(this->windowRefreshRate <= 0){
            this->windowRefreshRate = 60;
        }
        this->windowRefreshInterval = (int) floor(1000.0f/this->windowRefreshRate);
        std::cout << "Rendering with " << this->windowRefreshRate << " hz" << std::endl;
        
        glutDisplayFunc(&display_wrapper);
        glutReshapeFunc(&resize_wrapper);
        glutKeyboardFunc(&keyPressed_wrapper);
		//Arrow-Key functions
		glutSpecialFunc(&keySpecial_wrapper);
        glutTimerFunc(this->windowRefreshInterval, &timer_wrapper, 1);
        
        this->resize(this->width, this->height);
        //glutFullScreen();
        glutMainLoop();
    }

    /**
    * Resizes the window to a certain height
    * @param width The new width
    * @param height The new height
    */
    void Window::resize( int width, int height ){
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
    }

    /**
    * Displays the window
    */
    void Window::display(){

        if (!lightSwitch)             // If Not Light
        {
            glDisable(GL_LIGHTING);     // Disable Lighting
        }
        else                    // Otherwise
        {
            glEnable(GL_LIGHTING);      // Enable Lighting
        }

        //if (!LODSwitch)
        //{
        //    glDisable(GL_COLOR_MATERIAL);     // Disable Color Material
        //    glMaterialfv(GL_FRONT, GL_AMBIENT, LightAmbient);
        //    glMaterialfv(GL_FRONT, GL_DIFFUSE, LightDiffuse);
        //}
        //else                    // Otherwise
        //{
        //    glEnable(GL_COLOR_MATERIAL);      // Enable Color Material
        //    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //}

        // Clear The Screen And The Depth Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();       // Reset The View

		gluLookAt( this->eyeX, this->eyeY, this->eyeZ,
                   this->centerX, this->centerY, this->centerZ,
                   0.0, 0.0, -1.0);

		glTranslatef(this->centerX, this->centerY, this->centerZ);
		glRotatef(this->angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(this->centerX*(-1), this->centerY*(-1), this->centerZ*(-1));

        GLfloat mdl[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mdl);

        //get camera position
        camera_pos[0] = -(mdl[0] * mdl[12] + mdl[1] * mdl[13] + mdl[2] * mdl[14]);
        camera_pos[1] = -(mdl[4] * mdl[12] + mdl[5] * mdl[13] + mdl[6] * mdl[14]);
        camera_pos[2] = -(mdl[8] * mdl[12] + mdl[9] * mdl[13] + mdl[10] * mdl[14]);

        /*GLfloat matrix[16];
        glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
        eyeX = matrix[12];
        eyeY= matrix[13];
        eyeZ = matrix[14];*/

        //std::cout << "eyeX: " << eyeX << " eyeY: " << eyeY << " eyeZ: " << eyeZ << std::endl;
        //std::cout << "camera X: " << camera_pos[0] << " Y: " << camera_pos[1] << " Z: " << camera_pos[2] << std::endl;
		
        //update light position
        glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);        // Position The Light
        //glLightfv(GL_LIGHT2, GL_POSITION, SpotLightPosition);        // Position The Light

        // draw game objects
        this->game.update();
        glutSwapBuffers();
    }

    /**
    * Handles input events from the keyboard
    * @param key The key which was pressed
    * @param x The x position where the key was pressed
    * @param y The y position where the key was pressed
    */
    void Window::keyPressed(unsigned char key, int x, int y){
        Sleep(100);
        if(key == 27){
            glutDestroyWindow(this->window);
            exit(EXIT_SUCCESS);
        }
        this->game.input(key);
    }

    /**
     * Checks for arrow keys
     */
	void Window::specialKeyPressed(int key, int x, int y){
		switch(key){
			case GLUT_KEY_UP:
                if(this->eyeY > 4.0){
					this->eyeY -= 0.5;
				}
				break;
			
			case GLUT_KEY_DOWN:
                if(this->eyeY < 20.0){
					this->eyeY += 0.5;
				}
				break;
                
			case GLUT_KEY_RIGHT:
                this->angle = static_cast<GLfloat>(fmod(this->angle + 5.0, 360.0));
				break;
                
			case GLUT_KEY_LEFT:
                this->angle = static_cast<GLfloat>(fmod(this->angle - 5.0, 360.0));
				break;
            case GLUT_KEY_F1:
                lightSwitch = !lightSwitch;
				break;
            case GLUT_KEY_F2:
                if( LightPosition[2] >= -17.0f )
                    LightPosition[2] -= 0.5f;
				break;
            case GLUT_KEY_F3:
                if( LightPosition[2] <= 12.0f )
                    LightPosition[2] += 0.5f;
				break;
            case GLUT_KEY_F4:
                LODSwitch = !LODSwitch;
				break;
            
			default:
                return;
		}
	}

	/**
     * Redisplays the window and sets the timer to do it again
     * @param value integer which can be passed
     */
    void Window::redisplayTimer(int value) { 
        glutPostRedisplay();
        glutTimerFunc(this->windowRefreshInterval, &timer_wrapper, value);
    }

    /**
    * Returns a static instance of the window. Used for wrapper functions for OpenGL
    * @return The window instance
    */
    Window* Window::getInstance(){
        return Window::windowInstance;
    }

    Window::~Window(){
    }

}
