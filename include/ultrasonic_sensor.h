#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <modbus/modbus.h>
#include <string>

class UltrasonicSensor
{
    public:
        // Constructor: Initializes the Modbus context
        // port: The serial port name (e.g., "/dev/ttyUSB0")
        // baud_rate: Baud rate for RTU communication (e.g., 9600)
        // parity: Parity mode ('N', 'E', 'O') for "None", "Even" and "Odd"
        // data_bits: Number of data bits (e.g., 8)
        // stop_bits: Number of stop bits (e.g., 1)
        UltrasonicSensor(const std::string& port, int baud_rate, char parity, int data_bits, int stop_bits);

        // Destructor: Cleans up Modbus resources
        ~UltrasonicSensor();

        // Check if Modbus context is initialised
        bool is_initialised();

        // Connects to the Modbus RTU bus
        // Returns true on success, false on failure
        bool connect();

        // Disconnects from the Modbus RTU bus
        void disconnect();

        // Reads distance from a specific ultrasonic sensor (slave ID)
        // slave_id: The Modbus slave ID of the sensor (e.g., 1, 2, 3 or 4)
        // distance_mm: Reference to store the read distance in millimeters
        // Returns true on successful read, false on failure
        bool read_distance(int slave_id, uint16_t& distance_mm);

    private:
        std::string port_;
        modbus_t* ctx_;
        bool is_connected_;     // Internal check for if Modbus is connected
};

#endif