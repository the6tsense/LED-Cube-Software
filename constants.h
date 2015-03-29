#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {
public:
    static const int BAUDRATE = 38400;

    static const constexpr char* linuxPorts[30] =
                          {"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                           "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                           "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                           "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5",
                           "/dev/ttyAMA0","/dev/ttyAMA1","/dev/ttyACM0","/dev/ttyACM1",
                           "/dev/rfcomm0","/dev/rfcomm1","/dev/ircomm0","/dev/ircomm1"};
};

#endif // CONSTANTS_H
