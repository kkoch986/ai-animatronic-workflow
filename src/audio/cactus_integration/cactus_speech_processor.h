#ifndef CACTUS_SPEECH_PROCESSOR_H
#define CACTUS_SPEECH_PROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

// Forward declarations
namespace cactus {
    class Whisper;
    class Needle;
}

/**
 * @brief Cactus Compute speech processing for animatronic systems
 * 
 * This class integrates Cactus Compute's Whisper (speech-to-text) and Needle (tool calling)
 * capabilities into the animatronic workflow system.
 */
class CactusSpeechProcessor {
public:
    /**
     * @brief Constructor
     * @param model_path Path to Cactus Compute models
     */
    explicit CactusSpeechProcessor(const std::string& model_path = "");
    
    /**
     * @brief Destructor
     */
    ~CactusSpeechProcessor();
    
    /**
     * @brief Initialize the Cactus Compute components
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Process audio input for speech recognition
     * @param audio_data Raw audio data
     * @param sample_rate Audio sample rate
     * @return Transcribed text
     */
    std::string transcribeAudio(const std::vector<float>& audio_data, int sample_rate);
    
    /**
     * @brief Process audio file for speech recognition
     * @param audio_file Path to audio file
     * @return Transcribed text
     */
    std::string transcribeAudioFile(const std::string& audio_file);
    
    /**
     * @brief Execute tool calling based on natural language input
     * @param command Natural language command
     * @return Tool execution result
     */
    std::string executeToolCommand(const std::string& command);
    
    /**
     * @brief Get current system status
     * @return Status information
     */
    std::string getStatus() const;
    
    /**
     * @brief Set configuration parameters
     * @param config Configuration parameters
     */
    void setConfiguration(const std::map<std::string, std::string>& config);
    
private:
    // Cactus Compute components
    std::unique_ptr<cactus::Whisper> whisper_;
    std::unique_ptr<cactus::Needle> needle_;
    
    // Configuration
    std::string model_path_;
    bool initialized_;
    
    // Audio processing parameters
    int sample_rate_;
    int buffer_size_;
    
    /**
     * @brief Load Cactus Compute models
     * @return true if successful, false otherwise
     */
    bool loadModels();
    
    /**
     * @brief Process audio data through Cactus Compute
     * @param audio_data Audio data to process
     * @return Processed result
     */
    std::string processAudio(const std::vector<float>& audio_data);
};

#endif // CACTUS_SPEECH_PROCESSOR_H