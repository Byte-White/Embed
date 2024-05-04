cmake_minimum_required(VERSION 3.3)
project(Embed)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAGMA_VULKAN OFF)
set(MAGMA_OPENGL ON)
set(MAGMA_EMSCRIPTEN OFF)

# Add compile definitions if needed
# add_compile_definitions(MAGMA_NO_LOGGING)
# add_compile_definitions(MAGMA_NO_CORE_LOGGING)
# add_compile_definitions(MAGMA_NO_CLIENT_LOGGING)

add_subdirectory(vendor/Magma)
add_subdirectory(vendor/Catch2)

add_library(EmbedLib STATIC
    "app/src/Layers/AppLayer.cpp" 
    "app/src/Generator/EmbedManager.cpp" 
    "app/src/Generator/CodeGenerator.cpp" 
    "app/src/Generator/FileManager.cpp"
)

target_include_directories(EmbedLib
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/app/src
)

target_link_libraries(EmbedLib
    PUBLIC
    magma
)

add_executable(Embed 
    "app/src/main.cpp"
)

target_link_libraries(Embed
    PRIVATE
    EmbedLib
)

# Tests
add_subdirectory(app/tests)
