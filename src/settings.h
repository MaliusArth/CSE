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


// miliseconds until the next row appears
#define LINE_UPDATE_INTERVAL 5000

// min and max word length from the dictionary and typing
#define WORD_MIN_LENGTH 3
#define WORD_MAX_LENGTH 8

// rows and columns number on the game table
#define GAMETABLE_ROWS_NUM 11
#define GAMETABLE_COLUMNS_NUM 8

// how much space there should between cubes
#define CUBE_PADDING 0.05f

//ScorePanel values
#define MAX_SCORE 999999
#define MAX_SCORE_DISPLAY 6
#define MIN_SCORE 0

// points for letters
#define POINTS_A 1
#define POINTS_B 3
#define POINTS_C 3
#define POINTS_D 2
#define POINTS_E 1
#define POINTS_F 4
#define POINTS_G 2
#define POINTS_H 4
#define POINTS_I 1
#define POINTS_J 8
#define POINTS_K 5
#define POINTS_L 1
#define POINTS_M 3
#define POINTS_N 1
#define POINTS_O 1
#define POINTS_P 3
#define POINTS_Q 10
#define POINTS_R 1
#define POINTS_S 1
#define POINTS_T 1
#define POINTS_U 1
#define POINTS_V 4
#define POINTS_W 4
#define POINTS_X 8
#define POINTS_Y 3
#define POINTS_Z 10

// dictionary filepath
//#define DICTIONARY_PATH "resources/dict/dictionary.txt"
#define DICTIONARY_PATH "resources/dict/dict_debug.txt"

// textures directory
#define TEXTURES_DIRECTORY "resources/textures"

// LOD Level Ranges
#define LOD_RANGE_1 12.0f
#define LOD_RANGE_2 15.0f
#define LOD_RANGE_3 17.0f
