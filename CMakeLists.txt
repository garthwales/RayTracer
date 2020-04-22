cmake_minimum_required(VERSION 2.8)

# Use (slightly) modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project( RayTracer )

add_executable( rayTracer 
    AmbientLightSource.cpp
    AmbientLightSource.h
    Camera.cpp
    Camera.h
    CImg.h
    Colour.cpp
    Colour.h
    Cube.cpp
    Cube.h
    Cylinder.cpp
    Cylinder.h
    Direction.cpp
    Direction.h
    DirectionalLightSource.cpp
    DirectionalLightSource.h
    ImageDisplay.cpp
    ImageDisplay.h
    LightSource.cpp
    LightSource.h
    Material.h
	Material.cpp
    Matrix.cpp
    Matrix.h
    NonCopyable.h
    Normal.cpp
    Normal.h
    Object.cpp
    Object.h
	Octahedron.h
	Octahedron.cpp
    PinholeCamera.cpp
    PinholeCamera.h
    Plane.cpp
    Plane.h
    Point.cpp
    Point.h
    PointLightSource.cpp
    PointLightSource.h
    Ray.h
    RayIntersection.h
    Scene.cpp
    Scene.h
    SceneReader.cpp
    SceneReader.h
    Sphere.cpp
    Sphere.h
    SpotLightSource.cpp
    SpotLightSource.h
    Transform.cpp
    Transform.h
    Vector.cpp
    Vector.h
    rayTracerMain.cpp
    utility.h
)

