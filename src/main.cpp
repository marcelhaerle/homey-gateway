#include <iostream>
#include <string>

#include "Device.hpp"

using std::string;
using std::cout;
using std::endl;


int main(int argc, char **argv) {
    if (argc < 1) {
        cout << "USAGE: homey-gatway <mac>" << endl;
        return 1;
    }
    
    cout << "### Homey-Gateway ###" << endl;
    
    string address(argv[1]);
    Device device(address);
    if (device.connect()) {
        cout << "Device ID: " << device.readDeviceId() << endl;
        cout << "Temperature: " << device.readTemperature() << " C" << endl;
        cout << "Humidity: " << device.readHumidity() << " %" << endl;
        cout << "eCO2: " << device.readEco2() << " ppm" << endl;
        cout << "TVOC: " << device.readTvoc() << " ppb" << endl;

        device.disconnect();
    } else {
        cout << "Device " << address << " not found." << endl;
    }

    return 0;
}
