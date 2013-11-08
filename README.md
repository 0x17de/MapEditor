MapEditor
=========

Simple map editor with SDL2

Example: http://youtu.be/4mPZwm2lMEs

- Press space to toggle tile view, use arrow keys to move.
- Click to place tiles, right button to delete, middle to set active tile

Dependencies:
- OpenGL
- GLUT
- SDL2
- SDL2_image

How to compile on linux:
- Create a folder named 'build'
- $> cd build
- $> cmake ..
- $> make
- A binary should now exist inside the 'bin' folder

Missing:
- Save/load maps
- Background/foreground layers (stackable)
- Self definable events as layers (stackable) for e.g. damage, spawn, finish, ...
