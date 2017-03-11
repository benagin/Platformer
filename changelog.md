# Change Log: Platformmer Game

## 01/03/2017: Andrew
* Since last Log:
  * Created input manager
  * Created resource manager
  * Restructured the Font and made sure it rendered correctly
  * Created a Game object for controlling the game infrastructure
  * Began building an ini parser for inputting game configs
  * Created a window object
  * Moved font to graphic folder
* Completely added mouse movement and mouse click input controls. The game and window now know where the mouse was clicked.
* Nothing is rendering anymore because of a lack of a rendering system.

## 19/02/2017: Andrew
* Added a texture loading object
* Added a Texture rendering function to make sure the textures work. (They do)
* Made a little solder move around the screen using wasd and shift will speed him up (very 	 rudimentary).

## 18/02/2017: Ben
* Moving linker and framework includes from compile command to linker command in
  makefile.
* Fixing standards and formatting.

## 18/02/2017: Andrew
* Text Rendering works for the most part.
  * FTLoader: Partially works
  * Font: Works less than FTLoader.
* Created a Texture2D class.

## 17/02/2017: Andrew
* Running OpenGl 3.3 (can run 4.1).
* Created Font object to load in font but it uses stb truetype library instead of freetype
* Restructured the layout of the files.
* Added a utils director for utilities
* added graphics directors for graphics related files.
* Added a dubug option to the make file: make debug=1

## 16/02/2017: Ben
* Created the Project.
* FLLoader Object For loading fonts.
