#ifndef CACTUS_INTERFACE_H
#define CACTUS_INTERFACE_H

#include <string>
#include <vector>
#include <functional>

/**
 * @brief Interface for Cactus Compute integration with animatronic systems
 * 
 * This interface defines the contract for integrating Cactus Compute's
 * speech recognition and tool calling capabilities into the animatronic workflow.
 */
class CactusInterface {
public:
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~CactusInterface() = default;
    
    /**
     * @brief Initialize the Cactus Compute integration
     * @param model_path Path to Cactus Compute models
     * @return true if initialization successful, false otherwise
     */
    virtual bool initialize(const std::string& model_path) = 0;
    
    /**
     * @brief Deinitialize the Cactus Compute integration
     */
    virtual void deinitialize() = 0;
    
    /**
     * @brief Transcribe audio to text using Cactus Whisper
     * @param audio_data Raw audio data
     * @param sample_rate Audio sample rate
     * @return Transcribed text
     */
    virtual std::string transcribeAudio(const std::vector<float>& audio_data, int sample_rate) = 0;
    
    /**
     * @brief Transcribe audio file to text using Cactus Whisper
     * @param audio_file Path to audio file
     * @return Transcribed text
     */
    virtual std::string transcribeAudioFile(const std::string& audio_file) = 0;
    
    /**
     * @brief Execute tool command using Cactus Needle
     * @param command Natural language command
     * @return Tool execution result
     */
    virtual std::string executeToolCommand(const std::string& command) = 0;
    
    /**
     * @brief Get system status
     * @return Status information
     */
    virtual std::string getStatus() const = 0;
    
    /**
     * @brief Check if Cactus Compute is available and initialized
     * @return true if available, false otherwise
     */
    virtual bool isAvailable() const = 0;
    
    /**
     * @brief Set callback for transcription results
     * @param callback Function to be called with transcription results
     */
    virtual void setTranscriptionCallback(std::function<void(const std::string&)> callback) = 0;
    
    /**
     * @brief Set callback for tool execution results
     * @param callback Function to be called with tool execution results
     */
    virtual void setToolExecutionCallback(std::function<void(const std::string&)> callback) = 0;
};

#endif // CACTUS_INTERFACE_H