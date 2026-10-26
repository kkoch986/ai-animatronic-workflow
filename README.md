# AI Animatronic System

C++ implementation of AI animatronic system with facial detection, posture estimation, and OSC/DMX hardware control.

## Project Structure

This repository contains the C++ implementation for an AI-powered animatronic system that processes video and audio inputs to generate realistic responses through hardware actuators controlled via OSC and DMX protocols.

## Features

- Real-time facial detection and tracking
- Posture estimation from video input
- Audio processing and analysis
- OSC protocol support for external communication
- DMX protocol support for lighting and motor control
- Modular C++ architecture for easy maintenance and expansion

## Getting Started

### Prerequisites

To build and run this system, you'll need to install the following dependencies:

#### Arch Linux (using pacman):
```bash
sudo pacman -Syu base-devel cmake opencv dlib portaudio fftw liblo
```

#### Arch Linux (using yay):
```bash
yay -Syu base-devel cmake opencv dlib portaudio fftw liblo
```

#### Ubuntu/Debian (using apt):
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libopencv-dev libdlib-dev portaudio19-dev libfftw3-dev liblo-dev
```

#### Fedora:
```bash
sudo dnf install gcc-c++ cmake opencv-devel dlib-devel portaudio-devel fftw-devel liblo-devel
```

### Building the Project

1. Clone the repository:
```bash
git clone https://github.com/kkoch986/ai-animatronic-workflow.git
cd ai-animatronic-workflow
```

2. Create build directory and configure:
```bash
mkdir build && cd build
cmake ..
```

3. Compile the project:
```bash
make
```

4. Run the system:
```bash
./animatronic_system
```

## System Architecture

The system is organized into several modules:
- Video processing module (facial detection and landmark tracking)
- Audio processing module  
- Control system module
- Hardware interface module

## Phase 2: Facial Detection Implementation

The facial detection system includes:
- Real-time face detection using Dlib's frontal face detector
- 68-point facial landmark detection
- Visualization of detected faces and landmarks

## Phase 3: Audio Processing (In Progress)

The audio processing system will include:
- Real-time audio capture with PortAudio
- FFTW-based signal processing
- Feature extraction algorithms for speech and sound analysis
- Integration with control systems for audio-reactive responses

## Phase 4: Control System Implementation

The control system will handle:
- OSC protocol communication with external systems
- DMX512 protocol support for hardware control
- Mapping of video/audio inputs to physical movements
- Response generation algorithms for realistic animatronic behavior

## Docker Setup (Alternative Installation)

A Dockerfile is provided for containerized deployment:

```bash
# Build the Docker image
docker build -t ai-animatronic-system .

# Run the container
docker run -it --rm ai-animatronic-system
```

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

## License

This project is licensed under the MIT License - see the LICENSE file for details.