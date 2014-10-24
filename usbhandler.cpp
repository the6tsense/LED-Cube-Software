#include "usbhandler.h"

using namespace std;

usbHandler::usbHandler(int comPort) : port(comPort) {}

usbHandler::~usbHandler() {}

bool usbHandler::openPort(void) {
    if(RS232_OpenComport(port, 38400)) {
        cout << "Error opening connection" << endl;
        return false;
    }
    return true;
}

void usbHandler::test(bool xy) {
    unsigned char* stream = (unsigned char*) malloc(105 * sizeof(unsigned char));

    for(int i = 0; i < 105; i++) {
        if(xy) {
            stream[i] = 0x00;
        } else {
            stream[i] = 0x7F;
        }
    }
    if(xy) {
        cout << "on" << endl;
    } else {
        cout << "off" << endl;
    }

    stream[0] = 0x80;

    if(!RS232_SendBuf(port, stream, 105)) {
        cout << "Error sending bytes." << endl;
    }
    free(stream);
}

void usbHandler::sendUpdate(int cubeSize, array3d* const array) {
    int count = 0;
    int bytes = ceil(pow(cubeSize, 3.0) / 7);
    unsigned char* const stream = (unsigned char*) malloc(bytes * sizeof(unsigned char));
    unsigned char streamChar = 0x00;
    unsigned char* pstream = stream;

    for(int x = 0; x < cubeSize; x++) {
        for(int y = 0; y < cubeSize; y++) {
            for(int z = 0; z < cubeSize; z++) {
                if(count >= 7) {
                    *pstream++ = streamChar;
                    streamChar = 0x00;
                    count = 0;
                }

                streamChar |= (*array->operator ()(x, y, z) << count);
                count ++;
            }
        }
    }

    *pstream = streamChar;

    stream[0] |= (1 << 7);

    for(int i = 0; i < bytes; i++) {
        cout << hex << (int) stream[i] << ", ";
    }
    cout << endl;

    if(!RS232_SendBuf(port, stream, bytes)) {
        cout << "Error sending bytes." << endl;
    } else {
        cout << "sending succesfull" << endl;
    }

    free(stream);
}
