#ifndef CACTUS_INTEGRATION_H
#define CACTUS_INTEGRATION_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations for Cactus Compute classes
namespace cactus {
    class Whisper;
    class Needle;
}

/**
 * @brief Main integration point for Cactus Compute in animatronic systems
 * 
 * This header provides the main interface for integrating Cactus Compute's
 * speech recognition (Whisper) and tool calling (Needle) capabilities
 * into the animatronic workflow system.
 */
class CactusIntegration {
public:
    /**
     * @brief Initialize Cactus Compute integration
     * @param model_path Path to Cactus Compute models
     * @return true if initialization successful, false otherwise
     */
    static bool initialize(const std::string& model_path = "");
    
    /**
     * @brief Deinitialize Cactus Compute integration
     */
    static void deinitialize();
    
    /**
     * @brief Transcribe audio to text using Cactus Whisper
     * @param audio_data Raw audio data
     * @param sample_rate Audio sample rate
     * @return Transcribed text
     */
    static std::string transcribeAudio(const std::vector<float>& audio_data, int sample_rate);
    
    /**
     * @brief Transcribe audio file to text using Cactus Whisper
     * @param audio_file Path to audio file
     * @return Transcribed text
     */
    static std::string transcribeAudioFile(const std::string& audio_file);
    
    /**
     * @brief Execute tool command using Cactus Needle
     * @param command Natural language command
     * @return Tool execution result
     */
    static std::string executeToolCommand(const std::string& command);
    
    /**
     * @brief Get system status
     * @return Status information
     */
    static std::string getStatus();
    
    /**
     * @brief Check if Cactus Compute is available
     * @return true if available, false otherwise
     */
    static bool isAvailable();
    
private:
    // Private constructor to prevent instantiation
    CactusIntegration() = default;
    ~CactusIntegration() = default;
    
    // Static members for the integration
    static std::unique_ptr<cactus::Whisper> whisper_;
    static std::unique_ptr<cactus::Needle> needle_;
    static bool initialized_;
    static std::string model_path_;
};

#endif // CACTUS_INTEGRATION_H