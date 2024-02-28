# OpenGL Object Viewer Project README


## What is this project?
This project is a 3D object viewer that uses OpenGL to render 3D objects, and allows the user to navigate through the 3D space. The project is built using CMake.

## Technical Considerations

1. **Loading Delay**: Initial application launch may experience a delay due to the concurrent loading of multiple 3D objects. This is an expected behavior intended to ensure all models are ready for interaction.
2. **File Extension Workaround**: Encountered an issue with `.obj` file compatibility in VS Code, necessitating a rename of these files to `.obj.txt`. This workaround does not impact the functionality, as file loading is accomplished through `ifstream`, preserving the integrity of the object data.


## Screen Shots

## Showcasing the 3D Models and mouse movement
![](https://i.ibb.co/fD6H6rM/ezgif-2-b86338c856.gif)
### Textured Cube
![](https://i.ibb.co/1QHWv9K/Screenshot-2024-02-28-143936.png)

### Textured and colored Cube
![](https://i.ibb.co/JnPFtVs/Screenshot-2024-02-28-143956.png)

### Diffuse and Specular Lighting Dragon
![](https://i.ibb.co/qD1DrdV/Screenshot-2024-02-28-144522.png)

### Diffuse and Specular Lighting Detailed Dragon
![](https://i.ibb.co/Rpzv6BD/Screenshot-2024-02-28-144536.png)

### Diffuse and Specular Lighting and Color Dragon
![](https://i.ibb.co/5kpN8vy/Screenshot-2024-02-28-144544.png)

## Project Features

- **OpenGL Rendering**: Implements OpenGL to efficiently load and display 3D models, showcasing the capability to handle complex object rendering.
- **Interactive Navigation**: Features a custom-built navigation system using `W`, `S`, `D`, `A`, `E`, `Q` for movement within the 3D space (`E` for upward movement, `Q` for downward movement), enhancing the user's ability to explore 3D models.
- **Movement Toggle**: Incorporates a unique functionality to toggle movement on and off with the `Spacebar`, allowing for a more controlled viewing experience.

## Choices
- **The Project Choices**: out of the 11 Choices we hade I chose the first and the objects I rendered are:
    - `cube.obj`
    - `bunny.obj`
    - `dragon.obj`
    - `Cone.obj`
    - `Cylinder.obj`
    - `Sphere.obj`
    - `Cube.obj`

## Building and Running the Project
1) You clone the repo 
2) You use CmakeGui to build the project
3) You run the project

Normaly every library is included in the project so you don't need to install anything else.

The project is built using CMake, which is a cross-platform build system.



## Navigation Controls

- **Movement**: Use `W`, `S`, `D`, `A` to move in the respective directions.
- **Vertical Navigation**: `E` to ascend, `Q` to descend within the 3D environment.
- **Toggle Movement**: Press the `Spacebar` to enable or disable movement, facilitating focused observation of objects.

This project represents a practical application of OpenGL in rendering and navigating 3D objects, highlighting key learning outcomes in computer graphics. The challenges encountered and solutions implemented reflect a comprehensive understanding of both the theoretical and practical aspects of the subject matter.