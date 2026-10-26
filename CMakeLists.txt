cmake_minimum_required(VERSION 3.10)
project(AnimatronicSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

# Include directories
include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/video/video_processor.cpp
    src/audio/audio_processor.cpp
    src/control/control_system.cpp
)

# Create executable
add_executable(animatronic_system ${SOURCES})

# Link libraries
target_link_libraries(animatronic_system 
    ${OpenCV_LIBS}
    pthread
)