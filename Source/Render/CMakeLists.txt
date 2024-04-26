target_sources(
    "RayCaster"
    PRIVATE
    "Renderer.hpp"
    "Renderer.cpp"
)

add_subdirectory("Camera")
add_subdirectory("Light")
add_subdirectory("Material")
