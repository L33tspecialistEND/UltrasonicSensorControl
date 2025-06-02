#include "../include/ultrasonic_sensor.h"
#include <iostream>
#include <cerrno>

UltrasonicSensor::UltrasonicSensor(const std::string& port, int baud_rate, char parity, int data_bits, int stop_bits)
    : port_(port), ctx_(nullptr)
{
    // Create a new modbus RTU context
    ctx_ = modbus_new_rtu(port_.c_str(), baud_rate, parity, data_bits, stop_bits);
    if (ctx_ == nullptr)
        std::cerr << "Error: Unable to create the libmodus context for port " << port_ << '\n';
}

UltrasonicSensor::~UltrasonicSensor()
{
    if (ctx_ != nullptr)
    {
        modbus_free(ctx_);
        ctx_ = nullptr;
    }       
}

bool UltrasonicSensor::connect()
{
    if (ctx_ == nullptr)
    {
        std::cerr << "Error: Modbus context not initialised. Cannot connect.\n";
        return false;
    }
    if (modbus_connect(ctx_) == -1)
    {
        std::cerr << "Error: Connection to " << port_ << " failed: " << modbus_strerror(errno) << '\n';
        return false;
    }
    std::cout << "Successfully connected to Modbus RTU on port " << port_ << '\n';
    return true;
}