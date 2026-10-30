#ifndef DMX_CONTROLLER_H
#define DMX_CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>

namespace hardware {
    
class DMXController {
private:
    bool initialized;
    std::string device_path;
    int universe;
    
public:
    DMXController();
    ~DMXController();
    
    void initialize(const std::string& device_path, int universe);
    void sendData(const std::vector<uint8_t>& data);
    void release();
    
    bool isInitialized() const { return initialized; }
};

} // namespace hardware

#endif // DMX_CONTROLLER_H