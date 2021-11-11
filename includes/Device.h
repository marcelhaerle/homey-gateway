#pragma once

#include <string>
#include <vector>
#include <gattlib.h>

class Device {
private:
    std::string m_mac;
    gatt_connection_t* m_connection = nullptr;
    std::vector<uint8_t> readUUID(const std::string& uuid) const;
    std::string readString(const std::string& uuid) const;
    float readFloat(const std::string& uuid) const;
    int readInt(const std::string& uuid) const;
    const std::string DEVICE_ID_UUID   = "00000000-0000-0000-0000-000000000001";
    const std::string TEMPERATURE_UUID = "00000000-0000-0000-0000-000000000002";
    const std::string HUMIDITY_UUID    = "00000000-0000-0000-0000-000000000003";
    const std::string ECO2_UUID        = "00000000-0000-0000-0000-000000000004";
    const std::string TVOC_UUID        = "00000000-0000-0000-0000-000000000005";

public:
    explicit Device(std::string mac);
    bool connect();
    bool disconnect();
    std::string readDeviceId() const;
    float readTemperature() const;
    float readHumidity() const;
    int readEco2() const;
    int readTvoc() const;
};
