#ifndef DMX_CONTROLLER_H
#define DMX_CONTROLLER_H

#include <string>
#include <vector>

namespace hardware {
    
class DMXController {
private:
    bool initialized;
    std::string device_path;
    int universe;
    
public:
    DMXController();
    ~DMXController();
    
    void initialize(const std::string& device, int uni);
    void sendDMXData(const std::vector<unsigned char>& data);
    void setChannelValue(int channel, unsigned char value);
    void updateChannels();
    void release();
    
    // Helper methods for animatronic control
    void moveHead(int pan, int tilt);
    void controlLighting(int intensity);
    void activateActuator(int actuator_id, float power);
};

} // namespace hardware

#endif // DMX_CONTROLLER_H