#include "Device.h"
#include <algorithm>

using std::string;
using std::vector;

const string DEVICE_ID_UUID   = "00000000-0000-0000-0000-000000000001";
const string TEMPERATURE_UUID = "00000000-0000-0000-0000-000000000002";
const string HUMIDITY_UUID    = "00000000-0000-0000-0000-000000000003";
const string ECO2_UUID        = "00000000-0000-0000-0000-000000000004";
const string TVOC_UUID        = "00000000-0000-0000-0000-000000000005";

Device::Device(string mac): m_mac(mac) {}

bool Device::connect() {
    m_connection = gattlib_connect(NULL, m_mac.c_str(), GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
    return m_connection != NULL;
}

bool Device::disconnect() {
    if (m_connection != NULL) {
        if (gattlib_disconnect(m_connection) == GATTLIB_SUCCESS) {
            m_connection = NULL;
            return true;
        }
    }
    return false;
}

string Device::readString(string uuid) {
    vector<uint8_t> hexData = readUUID(uuid);
    if (hexData.size() > 0) {
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

float Device::readFloat(string uuid) {
    vector<uint8_t> hexData = readUUID(uuid);
    if (hexData.size() > 0) {
        uint8_t arr[hexData.size()];
        std::copy(hexData.begin(), hexData.end(), arr);
        float *value =  reinterpret_cast<float *>(arr);
        return *value;
    } else {
        return -999.0;
    }
}

int Device::readInt(string uuid) {
    vector<uint8_t> hexData = readUUID(uuid);
    if (hexData.size() > 0) {
        uint8_t arr[hexData.size()];
        std::copy(hexData.begin(), hexData.end(), arr);
        int *value =  reinterpret_cast<int *>(arr);
        return *value;
    } else {
        return -999;
    }
}

vector<uint8_t> Device::readUUID(string uuid) {
    vector<uint8_t> hexData;

    if (m_connection == NULL) {
        return hexData;
    }

    uint8_t *buffer = NULL;
    size_t len;

    uuid_t g_uuid;
    const char *c_uuid = uuid.c_str();

    if (gattlib_string_to_uuid(c_uuid, strlen(c_uuid) + 1, &g_uuid) == GATTLIB_SUCCESS) {
        if (gattlib_read_char_by_uuid(m_connection, &g_uuid, (void **)&buffer, &len) == GATTLIB_SUCCESS) {
            for (int i = 0; i < len; i++) {
                hexData.push_back(buffer[i]);
            }
        }
        free(buffer);
    }

    return hexData;
}

string Device::readDeviceId() {
    return readString(DEVICE_ID_UUID);
}

float Device::readTemperature() {
    return readFloat(TEMPERATURE_UUID);
}

float Device::readHumidity() {
    return readFloat(HUMIDITY_UUID);
}

int Device::readEco2() {
    return readInt(ECO2_UUID);
}

int Device::readTvoc() {
    return readInt(TVOC_UUID);
}
