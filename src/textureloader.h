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

#pragma once

#ifdef WIN32
    #include <Windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif
#include <map>
#include <string>

#include "imageloader.h"


namespace WordGL {

    class TextureLoader {

    public:
        static TextureLoader* getInstance();
        ~TextureLoader();
        void loadMipmappedTexture(Image *image, std::string filename);
        GLuint getTextureId(std::string key);

    private:
        TextureLoader(std::string path);
        std::map<std::string, GLuint> textureIds;
        static TextureLoader* loaderInstance;
        
    };

}