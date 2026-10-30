# Cactus Whistle Plugin for OpenWebUI

This plugin provides integration with the Cactus Whistle speech recognition library, enabling voice-to-text functionality within OpenWebUI.

## Overview

Cactus Whistle is a lightweight speech-to-text model developed by Cactus Compute. It features:
- Model size: 16.9 MB
- First token response time: 11 ms
- Supports 7 languages
- Efficient on-device processing

## Features

- Voice input transcription
- Integration with OpenWebUI's chat interface
- Configurable audio settings
- Cross-platform compatibility (macOS, Linux, Windows, Android, iOS)

## Installation

1. Place this plugin folder in the OpenWebUI plugins directory
2. Install dependencies: `pip install -r requirements.txt`
3. Configure plugin settings in the OpenWebUI interface

## Usage

The plugin can be used by:
- Activating voice input during chat sessions
- Transcribing audio files using the Cactus Whistle engine
- Integrating with other tools via the provided API

## Integration Guide

For actual implementation details, see `integration_guide.md`.