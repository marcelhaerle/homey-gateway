#pragma once

#include <string>
#include <vector>
#include <gattlib.h>

class Device {
private:
    std::string m_mac;
    gatt_connection_t* m_connection;
    std::vector<uint8_t> readUUID(std::string uuid);
    std::string readString(std::string uuid);
    float readFloat(std::string uuid);
    int readInt(std::string uuid);

public:
    Device(std::string mac);
    bool connect();
    bool disconnect();
    std::string readDeviceId();
    float readTemperature();
    float readHumidity();
    int readEco2();
    int readTvoc();
};
