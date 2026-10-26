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

1. Clone the repository
2. Install required dependencies (OpenCV, Dlib, PortAudio, FFTW, liblo)
3. Build using CMake
4. Run the system

## System Architecture

The system is organized into several modules:
- Video processing module
- Audio processing module  
- Control system module
- Hardware interface module