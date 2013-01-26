/**
 *  WordGL
 *  Copyright (C) 2012  Viktor Was <viktor.was@technikum-wien.at>
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
 * This class is responsible for loading the textures in the textures directory
 * and storing them for access
 */

#define EXTENSION ".bmp"

#include "common.h"

#include <cerrno>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <cstring>

#include <sys/types.h>
#ifndef WIN32
    #include "dirent.h"
#endif

#include "textureloader.h"
#include "imageloader.h"
#include "settings.h"

namespace WordGL {
	
	/**
	 * Singleton archicture to only load textures once
	 */
	TextureLoader* TextureLoader::loaderInstance = NULL;
	TextureLoader* TextureLoader::getInstance(){
		if(TextureLoader::loaderInstance == NULL){
			TextureLoader::loaderInstance = new TextureLoader(std::string(TEXTURES_DIRECTORY));
		}
		return TextureLoader::loaderInstance;
	}
	
	/**
	 * Loads all bmps in a directory
	 * @param path the path to the texture directory
	 */
    TextureLoader::TextureLoader(std::string path){

#ifdef WIN32
        WIN32_FIND_DATA search_data;

        memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

        HANDLE handle = FindFirstFile(std::string(path + "\\*"+EXTENSION).c_str(), &search_data);
  
        while(handle != INVALID_HANDLE_VALUE)
        {
            printf("Found file: %s\r\n", search_data.cFileName);

            std::string fileWithoutExtension = search_data.cFileName;
            fileWithoutExtension = fileWithoutExtension.substr(0, fileWithoutExtension.length() - strlen(EXTENSION));

            std::string filepath = path + "/"+ search_data.cFileName;
				
			Image* image = loadBMP(filepath);
			loadMipmappedTexture(image, fileWithoutExtension);
			delete image;
            
            if(FindNextFile(handle, &search_data) == FALSE)
            break;
        }
#else
		DIR *directoryHandle;
		struct dirent *currentDirectory;
		
		// check if path exists
		if((directoryHandle  = opendir(path.c_str())) == NULL) {
			std::cerr << "Error(" << errno << ") opening " << path << std::endl;
			exit(1);
		}
		
		// open directory 
		while ((currentDirectory = readdir(directoryHandle)) != NULL) {
			std::string file = std::string(currentDirectory->d_name);
			if(file.length() > 4){
				std::string fileWithoutExtension = file.substr(0, file.length() - strlen(EXTENSION));
				std::string fileExtension = file.substr(file.length() - strlen(EXTENSION), file.length());
				std::string filepath = path + std::string(currentDirectory->d_name);
				
				// check if extension is bmp
				if (fileExtension.compare(EXTENSION) == 0){
					Image* image = loadBMP(filepath);
					loadMipmappedTexture(image, fileWithoutExtension);
					delete image;
				}
			}
		}
		closedir(directoryHandle);
#endif
	}
	
	/**
	 * Turns the image into a mipmapped texture, then the textureid is stored in a vector
	 * @param *image
	 */
	void TextureLoader::loadMipmappedTexture(Image *image, std::string filename) {
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		
		//set texture environment parameters
		//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );	// default is GL_MODULATE
		
		
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		
		//From worst to best quality
		//GL_NEAREST
		//GL_LINEAR
		//GL_LINEAR_MIPMAP_NEAREST
		//GL_LINEAR_MIPMAP_LINEAR
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		//GL_REPEAT
		//GL_CLAMP
		//GL_CLAMP_TO_EDGE
		//NOTICE: additionally, YOU have to set glTexCoords relatively!!!
		
		gluBuild2DMipmaps(GL_TEXTURE_2D,
					3,
					image->width, image->height,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					image->pixels);
		
		// push filename and id into vector
		typedef std::pair<std::string, GLuint> stringIdPair;
		this->textureIds.insert(stringIdPair(filename, textureId));
	}
	
	/**
	 * Gets a texutreid based on its file name id. The id is the filename without
	 * the extension
	 */
	GLuint TextureLoader::getTextureId ( std::string key ) {
        std::map<std::string, GLuint>::const_iterator it = this->textureIds.find(key);  
        if(it != textureIds.end())
        {
		    return it->second;
        }
        std::cout << "Couldn't find texture named " << key << std::endl;
        return this->textureIds.begin()->second;
	}
	
	TextureLoader::~TextureLoader(){
		
	}
}
