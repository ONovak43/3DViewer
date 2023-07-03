# 3DViewer
**The project is still under development.**

3DViewer is an application that allows you to view 3D models saved in different formats (.obj, .gltf, .glb, .fbx). The application is written in C++ and uses OpenGL for rendering (objects are rendered on the graphics card).

Projetk využívá vlastní renderovací knihovnu (vč. vlastní matematické knihovny). Z knihoven třetích stran jsou použity knihovny *glad, glfw, imgui, lodepng, assimp a nativefiledialog*.

## Build
Clone the repository with the command 
```
git clone https://github.com/ONovak43/3DViewer
```
To generate a project for Visual Studio, run the *GenerateProject.bat* file in the root directory. 

## Application control
You navigate the application using the *W/A/S/D/Q/E* keys. Use the *P and O* keys to rotate the object. You can rotate the camera by pressing the mouse wheel. 

You can load an object into the application via menu - **File - Load**.

![alt 3DViewer](https://raw.githubusercontent.com/ONovak43/3DViewer/master/screens/3DViewer.png)
![alt Help v 3DViewer](https://raw.githubusercontent.com/ONovak43/3DViewer/master/screens/3DViewer_help.png)
