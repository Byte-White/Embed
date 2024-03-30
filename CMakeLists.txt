cmake_minimum_required(VERSION 3.3)
project(Embed)

set(CMAKE_CXX_STANDARD 17)

set(MAGMA_VULKAN OFF)
set(MAGMA_OPENGL ON)
set(MAGMA_EMSCRIPTEN OFF)


#add_compile_definitions(MAGMA_NO_LOGGING) #uncomment to stop all logging
#add_compile_definitions(MAGMA_NO_CORE_LOGGING) #uncomment to stop core logging
#add_compile_definitions(MAGMA_NO_CLIENT_LOGGING) #uncomment to stop client logging


add_subdirectory(vendor/Magma)

add_executable(Embed 
"app/src/main.cpp"
"app/src/Layers/AppLayer.cpp" 
"app/src/Generator/EmbedManager.cpp" 
"app/src/Generator/CodeGenerator.cpp" 
"app/src/Generator/FileManager.cpp"
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/app/src
)

target_link_libraries(Embed
PRIVATE
magma
)