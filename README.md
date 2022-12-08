# Creative Engine by Oriol Murcia Catalan

## Description
This engine has been developed for the UPC Master in Advanced Programming for AAA Videogames.
 
[Github](https://github.com/UriMurcia/Engine)

## Members
- Oriol Murcia Catalan

## Controls
- Right Click: Rotate camera
- Right Click + WASDQE: Rotate camera while moving. (W = Forward, S = Backwards, A = Left, D = Right, E = Up, Q = Down)
- Alt + Left Click: Orbit camera around the object.
- Alt + Right Click: Move camera forwards and backwards.
- Mouse Wheel: Zoom camera.
- F: Focus object.
- Arrows: Rotate camera.
- ESC: Quit.
- Shift: Duplicates speed while moving.
- Drag and drop .fbx files to the engine to load new 3D models.

## Additional functionalities for the assignment
- I've created a vector of objects in the ModuleRenderExercise that allows to add more than one object in the scene, althouhgh I only allowed one object at the same time for this assignment.
- On the loading texture process, I do 2 more steps than the requested to check if the path described by the .fbx is not an absolute path.
- I've created classes for the Editor windows.
- I show the number of triangles and vertices of each mesh.
- I made that the engine does not receive input if the window is not focused.

## Additional comments
- Make sure to click on the window it is wanted to use before using. I've tried to improve the engine using the ImGui::IsWindowFocused() function but can be better.