# Petal
WIP game engine in C++. Using OpenGL for graphics.

Note: Currently only supports x64 Windows and Visual Studio 2022 out of the box. To run:
1. Clone repository.
2. Run Setup.bat. This will generate Visual Studio solution/project files using Premake.
3. Open Petal.sln.
4. Select Release configuration and run (F5).

## Current Sandbox
<img src="/gallery/Sandbox.png" alt="Sandbox application using Petal Engine">

Controls:
Use wasd to move, space/shift to move Up/Down, right click and drag to turn camera.
Use GUI to adjust the following:
- Position of boxes and point lights (coloured cubes).
- Colour of point lights.
- Position and colour of directional light.
- Enable/disable diffuse map and specular map textures.

## Features
- 3D renderer using OpenGL
  - Phong shading model
  - Directional and point lights
  - Perspective camera
  - Transforms
  - Textures (diffuse, specular maps)
- Built-in shader library and support for custom GLSL shaders
- Event system
- Keyboard/mouse input
- Layers and overlays
- Debug UI through Dear ImGui
- Platform abstraction layer (currently only Windows/OpenGL are implemented)
- Engine compiles into static library for easy use in multiple projects
- Build system using Premake
- Precompiled header for faster build times

## Next steps
Planned features include:
- Loading 3D models from files
- Skeletal animation
- Physics
- PBR renderer
- Controller input
