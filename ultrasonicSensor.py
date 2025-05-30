import minimalmodbus    # for communicating with the sensor
import serial           # for serial connection
import sys              # for sys.exit()
import time             # for time.sleep()

port = "/dev/ttyUSB0"   # USB port name

try:
    instrument = minimalmodbus.Instrument(port = port, slaveaddress = 1)
    print("Connected to serial port")
except:
    print(f"Could not open instrument on port {port}")
    sys.exit(1)

# the following are defaults for the sensors
instrument.serial.baudrate = 9600
instrument.serial.bytesize = 8
instrument.serial.parity = serial.PARITY_NONE
instrument.serial.stopbits = 1
instrument.serial.timeout = 1       # seconds
instrument.mode = minimalmodbus.MODE_RTU
instrument.clear_buffers_before_each_transaction = True

# Communicate with sensor #1
try:
    instrument.address = 1
    time.sleep(0.05)
    sensor_one_distance = instrument.read_register(registeraddress = 0x0100, functioncode = 3)
    print(f"Sensor #1 responded. Distance: {sensor_one_distance} mm")
except Exception as e:
    print(f"Failed to communicate with sensor #1: {e}")

# Communicate with sensor #2
try:
    instrument.address = 2
    time.sleep(0.05)
    sensor_two_distance = instrument.read_register(registeraddress = 0x0100, functioncode = 3)
    print(f"Sensor #2 responded. Distance: {sensor_two_distance} mm")
except Exception as e:
    print(f"Failed to communicate with sensor #2: {e}")