CSE
===

University project: Computergraphics &amp; Special Effects

it is based upon the [bif4-cge](https://github.com/MaliusArth/bif4-cge) project
and is ported to Win32 (possible incompatibility with Mac OS X/Linux)

-

Dependencies:

# Build Instructions

To build it, you require

* [GLEW](http://glew.sourceforge.net/)
* [Glut/FreeGlut](http://freeglut.sourceforge.net/index.php#download)
* OpenGL


# Game description
This game is a mix of Bubble Bobble and Scrabble. Every 5 seconds a new line of
letters appears at the top of the creen. The existing ones move down by one row.

When the row reaches more than 11 rows, you lose. You also lose when you go below 0
points.

To remove the characters, type in words that are at between 3 and 8 characters.
If this word is in the dictionary you get points for it and the letters are removed.
When the word is longer than 3 characters you get a bonus for every following character.
The fourth character gets 2 times its points, the fifth gets 4 times its points,
the sixth gets 8 times its points and so on.

# Controls
* ESC - Quit
* BACKSPACE - Remove last typed letter
* ENTER - Confirm the word you typed in or restart game on gameover
* LEFT ARROW, RIGHT ARROW - Rotate horizontally
* UP ARROW, DOWN ARROW - Rotate vertically
* F1 - Toggle Lighting
* F2, F3 - Move Light Source
* F4 - Toggle LOD Highlighting

Words can only contain ASCII characters

# Author
* Viktor Was:		graphics, drawing, texturing, lighting
