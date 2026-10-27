cmake_minimum_required(VERSION 3.10)
project(ai_animatronic_workflow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(dlib REQUIRED)
find_package(PortAudio REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(liblo REQUIRED)

# Include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${DLIB_INCLUDE_DIRS}
    ${PORTAUDIO_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
    ${LO_INCLUDE_DIRS}
    include
    include/video
    include/control
    include/audio
    include/hardware
)

# Source files
set(SOURCES
    src/main.cpp
    src/video/video_processor.cpp
    src/video/facial_analysis.cpp
    src/control/control_system.cpp
    src/audio/audio_processor.cpp
    src/audio/speech_processor.cpp
    src/hardware/dmx_controller.cpp
)

# Create executable
add_executable(animatronic_system ${SOURCES})

# Link libraries
target_link_libraries(animatronic_system
    ${OpenCV_LIBS}
    ${DLIB_LIBRARIES}
    ${PORTAUDIO_LIBRARIES}
    ${FFTW3_LIBRARIES}
    ${LO_LIBRARIES}
)

# Install target
install(TARGETS animatronic_system DESTINATION bin)