# Software Renderer & Ray Tracer

A complete educational graphics engine implemented in C++, featuring both a **traditional rasterization pipeline** and a **Whitted-style ray tracer**.
This project was developed incrementally as part of a university-level computer graphics course and demonstrates core rendering concepts from first principles.

---

## Features

### Rasterization Pipeline
- Full vertex → fragment graphics pipeline
- Modeling, viewing, projection, and viewport transformations
- Back-face culling
- Clipping against the normalized device coordinate (NDC) volume
- Wireframe and filled triangle rendering
- Perspective-correct interpolation
- Per-fragment Phong lighting
- Depth buffering and hidden surface removal
- Texture mapping
- Fog effects (linear, exponential)
- CPU-based line and triangle rasterization

### Ray Tracer
- Recursive ray tracing
- Opaque and transparent object handling
- Shadow rays with dielectric awareness
- Reflection and refraction using Fresnel equations
- Dielectric materials (glass-like surfaces)
- Anti-aliasing via supersampling
- Texture mapping in ray-traced scenes
- Physically motivated lighting model

### Geometry Support
- Explicit geometry via OBJ loading
- Implicit surfaces:
  - Planes
  - Spheres
  - Disks
  - Cylinders (open and closed)
  - Cones
  - Ellipsoids
  - General quadric surfaces
- Accurate surface normals and texture coordinates

### Lighting
- Ambient, diffuse, and specular components
- Positional lights
- Directional lights
- Spotlights with cone falloff
- Distance attenuation
- Shadow testing

---

## Project Structure

```
.
├── camera.*
├── framebuffer.*
├── fragmentops.*
├── vertexops.*
├── rasterization.*
├── raytracer.*
├── iscene.*
├── ishape.*
├── eshape.*
├── light.*
├── colorandmaterials.*
├── image.*
├── utilities.*
├── exercises/
└── assets/
```

---

## Example Programs

The repository includes multiple standalone test programs demonstrating specific concepts:

- 2D and 3D transformations
- Matrix operations using GLM
- Intersection testing
- Graphics pipeline stages
- Hidden surface removal
- Basic and textured ray tracing
- Transparent and dielectric materials
- Camera and lighting experiments

Each exercise is self-contained and focuses on a specific rendering topic.

---

## Technologies Used

- **Language:** C++
- **Math Library:** GLM
- **Rendering:** CPU-based (no OpenGL / Vulkan)
- **Image Format:** PPM (P3 / P6)

---

## Educational Goals

This project emphasizes:
- Understanding rendering algorithms at a low level
- Implementing the graphics pipeline without GPU abstraction
- Comparing rasterization vs ray tracing approaches
- Learning physically motivated lighting models
- Building reusable rendering architecture

It is intended as a learning and demonstration tool rather than a real-time engine.

---

## Building & Running

This project is designed to be compiled using a standard C++ compiler with GLM installed.

Example (Linux/macOS):

```bash
g++ -std=c++17 *.cpp -o renderer
./renderer
```

Specific exercises may require compiling individual source files.

---

## Notes

- This codebase was developed incrementally across multiple assignments.
- Some files contain intentionally unimplemented sections depending on the exercise.
- Performance optimizations were not a primary goal; clarity and correctness were prioritized.

---

## License

This project is provided for educational and portfolio purposes.
Some framework code and structure were provided as part of coursework.
