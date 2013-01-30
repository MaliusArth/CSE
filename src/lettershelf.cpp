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
 * Represents the shelf were we input characters, also manages the input words
 * and draws all elements that belong to it
 */

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "lettershelf.h"
#include "dimension.h"
#include "point.h"
#include "settings.h"
#include "lettercube.h"

namespace WordGL {

    /**
     * @param startPoint the startPoint where the object should be drawn
     * @param dimension the dimesions of the object
     */
    LetterShelf::LetterShelf(Point startPoint, Dimension dimension):
								GLCube(startPoint,dimension),
								cubeDimension(Dimension(dimension.getWidth()/WORD_MAX_LENGTH, 
														(dimension.getWidth()/WORD_MAX_LENGTH)-dimension.getHeight(), 
														dimension.getWidth()/WORD_MAX_LENGTH)),
								currentPoint(startPoint)
								{
		this->currentPoint.setYCoord(this->height);
    }

	
	/**
     * Add a new character to the shelf
     */
	void LetterShelf::push(char character){
		//If the lettershelf is full, don't do anything
		if(this->cubes.size() >= WORD_MAX_LENGTH) {
			return;
		}
		//The first cube gets on the initial-position of the lettershelf
		if(this->cubes.empty()){
			this->currentPoint.setXCoord(startX);
		} else{
			GLfloat currentX = this->currentPoint.getXCoord();
			this->currentPoint.setXCoord(currentX + cubeDimension.getWidth());
		}
		//LetterCube cube erstellen
		this->cubes.push_back(new LetterCube(this->currentPoint, this->cubeDimension, character));
	}

	/**
     * Removes the last character from the shelf
     */
	void LetterShelf::pop(){	
		if(this->cubes.empty()){
			this->currentPoint.setXCoord(startX);
		}
		else{
			GLfloat currentX = this->currentPoint.getXCoord();
			this->currentPoint.setXCoord(currentX - cubeDimension.getWidth());
			this->cubes.pop_back();
		}
	}	

	/**
     * Removes all characters from the shelf
     * @return the characters which were removed
     */
	std::vector<char> LetterShelf::clear(){
		std::vector<char> ret;
		for(unsigned int i = 0; i < this->cubes.size(); i++){
			ret.push_back(this->cubes[i]->getLetter());
		}
		
		//Clear the cube-vector
		this->cubes.clear();
		
		//Reset position-marker
		this->currentPoint.setXCoord(this->startX);
		
		return ret;
	}

	/**
     * Draws the lettershelf and its components
     */
    void LetterShelf::draw() {
		glPushMatrix();
		
		//Draw the panel itself
        //this->move(this->startX, this->startY, this->startZ);
        //this->setColor(1.0f, 1.0f, 1.0f);
        this->setTexture("wood");

		GLCube::draw();

		//Draw the input-cubes
		for(unsigned int i = 0 ; i < this->cubes.size(); i++){
			this->cubes[i]->draw();
		}
		
        glPopMatrix();
    }

    LetterShelf::~LetterShelf() {
        this->cubes.clear();
    }
}