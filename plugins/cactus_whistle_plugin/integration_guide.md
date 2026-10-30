# Cactus Whistle Integration Guide

This document provides detailed instructions for integrating the Cactus Whistle library with OpenWebUI.

## About Cactus Whistle

Cactus Whistle is a lightweight speech-to-text model developed by Cactus Compute. It's designed for efficient on-device processing and supports multiple languages with a small model size (16.9 MB).

## Installation

### Prerequisites
- Python 3.7 or higher
- pip package manager

### Installing the Cactus Whistle Library

```bash
pip install cactus-needle
```

This will install both the Needle (tool calling) and Whistle (speech-to-text) components.

## Core Components

The Cactus Whistle library provides two main components:

1. **Needle**: Tool calling functionality
2. **Whistle**: Speech-to-text recognition

## API Usage

### Basic Usage

```python
import needle

# Initialize the library
whistle = needle.Whistle()
```

### Transcribing Audio

```python
# Transcribe an audio file
result = whistle.transcribe("path/to/audio.wav")
print(result["text"])
```

### Using Tool Calling (Needle)

```python
import needle

@needle.tool
def get_weather(city: str):
    """Get the current weather for a city."""
    return {"city": city, "temp_c": 27, "sky": "clear"}

agent = needle.Needle(tools=[get_weather])
print(agent.run("what's it like in Lagos right now?")["results"])
```

## Integration with OpenWebUI

### Plugin Structure

The plugin follows the standard OpenWebUI plugin structure:
- `main.py` - Main implementation
- `config.json` - Plugin configuration
- `README.md` - Documentation
- `requirements.txt` - Dependencies

### Key Methods

1. **transcribe(audio_file)**: Transcribes audio files to text
2. **generate_whistle(text)**: Generates whistle sounds from text (via tool calling)
3. **get_settings()**: Retrieves current plugin settings
4. **set_settings(settings)**: Updates plugin configuration

## Configuration Options

The plugin supports the following configuration options:

```json
{
  "whistle_duration": 3.0,
  "base_frequency": 440.0,
  "sample_rate": 22050,
  "language": "en",
  "model_path": "",
  "enable_voice_input": true
}
```

## Testing the Integration

To test if the integration works:

1. Install the plugin in OpenWebUI
2. Ensure `cactus-needle` is installed in your Python environment
3. Test transcription functionality with sample audio files
4. Verify that voice input works properly in the chat interface

## Troubleshooting

### Common Issues

1. **Import Error**: If you see "ModuleNotFoundError: No module named 'needle'", install the library:
   ```bash
   pip install cactus-needle
   ```

2. **Audio Processing Errors**: Ensure audio files are in supported formats (WAV, MP3).

3. **Permission Issues**: On some systems, you might need to install system dependencies for audio processing.

## Performance Considerations

- The Cactus Whistle model is optimized for mobile and edge devices
- First token response time: 11 ms
- Supports real-time transcription
- Efficient memory usage

## Future Enhancements

The plugin can be extended with:
- Custom voice models
- Language-specific optimizations
- Integration with other AI services
- Advanced audio processing features