# GearWave

**GearWave** is a modular **C++17** game engine built on **OpenGL**, designed for cross‑platform rendering, audio, physics, and scripting.

## 📝 Features

- Modern CMake structure for macOS, Linux, Windows :contentReference[oaicite:12]{index=12}  
- GLAD + GLFW integration for context and function loading :contentReference[oaicite:13]{index=13}  
- Clear separation: `include/`, `src/`, `external/`, `tests/`, `assets/` :contentReference[oaicite:14]{index=14}  
- Unit tests with [doctest](https://github.com/onqtam/doctest) :contentReference[oaicite:15]{index=15}  
- Optional VSCode and CLion support via CMake :contentReference[oaicite:16]{index=16}

## 🚀 Getting Started

### Prerequisites

- **CMake** ≥ 3.16  
- A C++17‑capable compiler (Clang, GCC, MSVC)  
- **Git** for version control  
- (Optional) **Git LFS** for large assets  

### Clone & Build

```bash
git clone https://github.com/Ishan1231/GearWave.git
cd GearWave
mkdir build && cd build
cmake ..
cmake --build . --config Release

NOTE: NEED SDL2 INSTALLED TO RUN.