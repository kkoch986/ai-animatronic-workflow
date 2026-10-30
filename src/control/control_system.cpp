#include "control/control_system.h"
#include <lo/lo.h>
#include <iostream>
#include <vector>

namespace control {
    
ControlSystem::ControlSystem() : initialized(false), osc_port(8000) {
    // Constructor implementation
}

ControlSystem::~ControlSystem() {
    // Destructor implementation
    if (initialized) {
        release();
    }
}

void ControlSystem::initialize(const std::string& address, int port) {
    try {
        osc_address = address;
        osc_port = port;
        initialized = true;
        std::cout << "Control system initialized successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error initializing control system: " << e.what() << std::endl;
        initialized = false;
    }
}

void ControlSystem::sendOSCMessage(const std::string& path, const std::vector<float>& values) {
    if (!initialized) {
        return;
    }
    
    try {
        // Create OSC address
        lo_address addr = lo_address_new(osc_address.c_str(), std::to_string(osc_port).c_str());
        
        if (addr == nullptr) {
            std::cerr << "Failed to create OSC address" << std::endl;
            return;
        }
        
        // Create OSC message
        lo_message msg = lo_message_new();
        
        // Add float values to the message
        for (const auto& value : values) {
            lo_message_add_float(msg, value);
        }
        
        // Send the message
        lo_send_message(addr, path.c_str(), msg);
        
        // Clean up
        lo_message_free(msg);
        lo_address_free(addr);
        
    } catch (const std::exception& e) {
        std::cerr << "Error sending OSC message: " << e.what() << std::endl;
    }
}

void ControlSystem::processVideoFrame(const cv::Mat& frame) {
    // This method will be implemented in later phases
    // For now, it's a placeholder that demonstrates integration
    if (!initialized || frame.empty()) {
        return;
    }
    
    // In a real implementation, this would:
    // 1. Process the video frame for facial features
    // 2. Map these features to control parameters
    // 3. Send OSC messages to control hardware
    
    std::cout << "Processing video frame through control system" << std::endl;
}

void ControlSystem::release() {
    initialized = false;
    std::cout << "Control system released" << std::endl;
}

} // namespace control