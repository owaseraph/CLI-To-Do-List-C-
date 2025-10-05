cmake_minimum_required(VERSION 3.10)
project(ToDoList)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)
include_directories(third_party/imgui)
include_directories(third_party/imgui/backends)

# Add source files
set(SOURCES_GUI
    src/main_gui.cpp
    src/glad.c
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)

set(SOURCES_CLI
    src/main.cpp
    src/glad.c
)

# Link GLFW and OpenGL libraries
set(LIBS
    ${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a
    opengl32
    gdi32
)

# GUI executable
add_executable(ToDoListGUI ${SOURCES_GUI})
target_link_libraries(ToDoListGUI ${LIBS})

# CLI executable
add_executable(ToDoListCLI ${SOURCES_CLI})
target_link_libraries(ToDoListCLI ${LIBS})