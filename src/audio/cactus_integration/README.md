# Cactus Compute Integration for Animatronic Systems

This directory contains the integration of Cactus Compute's speech recognition and tool calling capabilities into the animatronic workflow system.

## Overview

The Cactus Compute integration provides:
- **Whisper**: Speech-to-text functionality for processing voice commands
- **Needle**: Tool calling capability for executing actions based on natural language

## Components

### 1. Cactus Integration Header (`cactus_integration.h`)
- Main interface for integrating Cactus Compute capabilities
- Provides static methods for initialization, transcription, and tool execution
- Handles system status and availability checks

### 2. Cactus Integration Implementation (`cactus_integration.cpp`)
- Core implementation of the integration layer
- Mock implementations for demonstration purposes
- Actual Cactus Compute library integration would be implemented here

### 3. Speech Processor Header (`cactus_speech_processor.h`)
- Object-oriented interface for speech processing
- Provides methods for audio transcription and tool command execution
- Includes configuration management

### 4. Speech Processor Implementation (`cactus_speech_processor.cpp`)
- Complete implementation of the speech processor class
- Handles initialization, audio processing, and Cactus Compute integration
- Includes mock implementations for demonstration

## Integration Process

The integration follows these steps:
1. Initialize Cactus Compute components (Whisper and Needle)
2. Load required models and configuration
3. Process incoming audio data through Whisper
4. Interpret natural language commands with Needle
5. Execute appropriate animatronic actions

## Usage Example

```cpp
// Initialize the integration
CactusIntegration::initialize("/path/to/models");

// Transcribe audio
std::vector<float> audio_data = {0.1, 0.2, 0.3, ...};
std::string transcription = CactusIntegration::transcribeAudio(audio_data, 22050);

// Execute tool command
std::string result = CactusIntegration::executeToolCommand("move your head to the left");
```

## Model Requirements

The integration requires:
- Cactus Compute Whisper model (16.9 MB)
- Cactus Compute Needle tools configuration
- Audio processing libraries (PortAudio, FFTW3)

## Configuration

The system can be configured through:
- Model paths
- Audio sample rates
- Processing parameters
- Hardware interfaces

## Mock Implementation

For development and testing purposes, mock implementations are provided that simulate:
- Audio transcription results
- Tool execution responses
- System initialization delays

These mock implementations allow for testing without requiring the actual Cactus Compute library.