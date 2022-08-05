# Render
> Software Renderer by Win32 and C++

> Reference Book: "fundamentals of computer graphics(5th)"

## Directory Structure
~~~
├── display             // Output Interface of Image
│   ├── win32.cpp
│   └── win32.h
├── graphics            // Computer Graphic Algorithm
│   ├── common.cpp
│   ├── common.h
│   ├── lights.cpp
│   ├── lights.h
│   ├── materials.cpp
│   ├── materials.h
│   ├── surfaces.cpp
│   ├── surfaces.h
│   ├── transformation.cpp
│   ├── transformation.h
│   ├── utils.cpp
│   └── utils.h
├── main.cpp            // Image-Order Render Entry
└── test.cpp            // Object-Order Render Entry
~~~


## Rendering
There are two ways to render:
- object-order rendering
- image-order rendering

**Ray Tracing** is an image-order algorithm.

### Steps of Ray Tracing
1. ray generation (_Viewing Ray_)
2. ray intersection
3. shading

## Done
1. Ray-Sphere Intersection
2. Ray-Triangle Intersection

## Types of Lights
- Point lights
- Directional lights
- Ambient lights
- Area lights
- Environment lights