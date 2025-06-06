#include <iostream>
#include <thread>
#include <modbus/modbus.h>          // library to communicate with the sensor

int main() {
    const char* port{ "/dev/ttyUSB0" };     // USB port name
    int numSlaves{ 2 };                     // Number of sensors to communicate with

    // Creates a pointer to a structure with defaults for sensor communication
    modbus_t* ctx = modbus_new_rtu(port, 9600, 'N', 8, 1);

    if (ctx == nullptr) 
    {
        std::cerr << "Unable to create the libmodbus context\n";
        return 1;
    }
    
    // Iterate 5 times to read from the 2 sensors every 2 seconds
    for (int jjj{}, times{5}; jjj <= times; ++jjj)
    {
        // Iterate twice to read from 2 sensors
        for (int iii{}; iii < numSlaves; ++iii)
        {
            if (modbus_set_slave(ctx, iii + 1) == -1)
            {
                std::cerr << "Invalid slave ID\n";
                modbus_free(ctx);
                return 1;
            }

            if (modbus_connect(ctx) == -1)
            {
                std::cerr << "Connection failed\n";
                modbus_free(ctx);
                return 1;
            }

            uint16_t distance{};
            int rc = modbus_read_registers(ctx, 0x0100, 1, &distance);
            if (rc == -1)
            {
                std::cerr << "Failed to read register\n";
            } 
            else 
            {
                std::cout << "Sensor #" << iii + 1 << " responded. Distance: " << distance << " mm" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}