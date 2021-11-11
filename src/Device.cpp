#include "Device.hpp"
#include <algorithm>

using std::string;
using std::vector;

Device::Device(string mac) : m_mac(std::move(mac)) {}

bool Device::connect() {
    m_connection = gattlib_connect(nullptr, m_mac.c_str(), GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
    return m_connection != nullptr;
}

bool Device::disconnect() {
    if (m_connection != nullptr) {
        if (gattlib_disconnect(m_connection) == GATTLIB_SUCCESS) {
            m_connection = nullptr;
            return true;
        }
    }
    return false;
}

string Device::readString(const string &uuid) const {
    vector<uint8_t> hexData = readUUID(uuid);
    if (!hexData.empty()) {
        uint8_t arr[hexData.size()];
        std::copy(hexData.begin(), hexData.end(), arr);
        string value;
        for (uint8_t i: arr) {
            value.push_back(i);
        }
        return value;
    } else {
        return "";
    }
}

float Device::readFloat(const string &uuid) const {
    vector<uint8_t> hexData = readUUID(uuid);
    if (!hexData.empty()) {
        uint8_t arr[hexData.size()];
        std::copy(hexData.begin(), hexData.end(), arr);
        auto value = reinterpret_cast<float *>(arr);
        return *value;
    } else {
        return -999.0;
    }
}

int Device::readInt(const string &uuid) const {
    vector<uint8_t> hexData = readUUID(uuid);
    if (!hexData.empty()) {
        uint8_t arr[hexData.size()];
        std::copy(hexData.begin(), hexData.end(), arr);
        auto value = reinterpret_cast<int *>(arr);
        return *value;
    } else {
        return -999;
    }
}

vector<uint8_t> Device::readUUID(const string &uuid) const {
    vector<uint8_t> hexData;

    if (m_connection == nullptr) {
        return hexData;
    }

    uint8_t *buffer = nullptr;
    size_t len;

    uuid_t g_uuid;
    const char *c_uuid = uuid.c_str();

    if (gattlib_string_to_uuid(c_uuid, strlen(c_uuid) + 1, &g_uuid) == GATTLIB_SUCCESS) {
        if (gattlib_read_char_by_uuid(m_connection, &g_uuid, (void **) &buffer, &len) == GATTLIB_SUCCESS) {
            for (int i = 0; i < len; i++) {
                hexData.push_back(buffer[i]);
            }
        }
        free(buffer);
    }

    return hexData;
}

string Device::readDeviceId() const {
    return readString(DEVICE_ID_UUID);
}

float Device::readTemperature() const {
    return readFloat(TEMPERATURE_UUID);
}

float Device::readHumidity() const {
    return readFloat(HUMIDITY_UUID);
}

int Device::readEco2() const {
    return readInt(ECO2_UUID);
}

int Device::readTvoc() const {
    return readInt(TVOC_UUID);
}
