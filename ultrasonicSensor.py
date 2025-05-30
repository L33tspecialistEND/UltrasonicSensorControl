import minimalmodbus    # for communicating with the sensor
import serial           # for serial connection
import sys              # for sys.exit()

slave_id = 1            # default for all sensors
port = "/dev/ttyUSB0"   # USB port name

try:
    instrument = minimalmodbus.Instrument(port = port, slaveaddress = slave_id)
    print("Connected to the sensor")
except:
    print(f"Could not connect to the sensor on port {port}")
    sys.exit(1)

# the following are defaults for the sensor
instrument.serial.baudrate = 9600
instrument.serial.bytesize = 8
instrument.serial.parity = serial.PARITY_NONE
instrument.serial.stopbits = 1
instrument.serial.timeout = 1       # seconds
instrument.mode = minimalmodbus.MODE_RTU

try:
    distance = instrument.read_register(registeraddress = 0x0100, functioncode = 3)
    print(f"Sensor responded. Distance: {distance} mm")
except Exception as e:
    print(f"Failed to communicate with sensor {slave_id}: {e}")