# StarWars Animation Lua/C++ and OpenGL


A C++ and OpenGL-based 3D animation project that demonstrates a **Lua-driven cinematic sequencing system**. The project uses Lua scripts to control and choreograph game objects, cameras, spacecraft, fighters, and asteroids while the underlying animation and gameplay systems are implemented in C++.

The animation system is built around a **command-based architecture**, allowing complex sequences to be composed from reusable commands such as timed movement, rotation, scaling, curve following, object following, look-at behavior, spawning, and timed delays. Commands can be grouped and executed either **serially or in parallel**, making it possible to synchronize multiple objects and camera movements within a scene.

The `World.lua` script acts as the cinematic director, defining multiple scenes and coordinating the Millennium Falcon, camera, and dynamically spawned asteroids through timed sequences and Bézier-style movement paths.

The C++ side provides the underlying **GameObject, EntityManager, camera, input, spacecraft, fighter, asteroid, and Lua integration systems**, while Lua provides a flexible high-level interface for authoring the animation without hard-coding each sequence into the engine.

### Key Features

* **Lua-driven cinematic animation**
* **C++ / Lua integration**
* Command-based animation architecture
* Serial and parallel command execution
* Timed movement, rotation, and scaling
* Curve-based object animation
* Object following and look-at behavior
* Dynamic game-object spawning
* Camera choreography
* Entity and GameObject management
* OpenGL-based 3D rendering
* Multi-scene cinematic sequencing
