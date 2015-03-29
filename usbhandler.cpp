#include "usbhandler.h"

using namespace std;

usbHandler::usbHandler() : m_port(0) {}

usbHandler::~usbHandler() {
    RS232_CloseComport(m_port);
}

bool usbHandler::openPort(void)
{
    //initialize variables
    int found = 0;
    int amountFound = 0;

    //the rs232 file has 30 ports for linux to check
    #ifdef __linux__ /*linux*/
    int ports = 29;

    //and 16 ports for windows
    #else /*windows*/
    int ports = 15;

    #endif

    //go through all the available ports
    for(; ports >= 0; ports--)
    {
        //see if a connection can be established
        if(!RS232_OpenComport(ports, 38400))
        {
            //if a sender was found remember its port number
            found = ports;

            //increase amount of found senders
            amountFound++;

            //and close the connection again
            RS232_CloseComport(ports);
        }
    }

    //if no sender was found
    if(amountFound < 1)
    {
        //print an error message and quit
        std::cout << "No sender connected." << std::endl;
        return false;

    //if more than one sender was found
    } else if(amountFound > 1)
    {
        //print an error message and quit
        std::cout << "More than one sender found. Please make sure only one is connected" << std::endl;
    }

    std::cout << "connecting to: " << found << std::endl;

    //try to open the comport found again
    if(RS232_OpenComport(found, 38400))
    {
        //in the unlikely case this fails, quit
        std::cout << "Something odd happened" << std::endl;
        return false;
    }

    //remember port
    m_port = found;

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

    if(!RS232_SendBuf(m_port, stream, 105)) {
        cout << "Error sending bytes." << endl;
    }
    free(stream);
}

void usbHandler::sendUpdate(void) {
    int count = 0;
    int bytes = ceil(pow(Effect::getCubeSize(), 3.0) / 7);
    unsigned char* const stream = (unsigned char*) malloc(bytes * sizeof(unsigned char));
    unsigned char streamChar = 0x00;
    unsigned char* pstream = stream;

    for(int x = 0; x < Effect::getCubeSize(); x++) {
        for(int y = 0; y < Effect::getCubeSize(); y++) {
            for(int z = 0; z < Effect::getCubeSize(); z++) {
                if(count >= 7) {
                    *pstream++ = streamChar;
                    streamChar = 0x00;
                    count = 0;
                }

                streamChar |= (*Effect::s_cubearray(x, y, z) << count);
                count ++;
            }
        }
    }

    *pstream = streamChar;

    stream[0] |= (1 << 7);

    #ifdef STREAMDEBUG
    for(int i = 0; i < bytes; i++) {
        cout << hex << (int) stream[i] << ", ";
    }
    cout << endl;
    #endif

    if(!RS232_SendBuf(m_port, stream, bytes)) {
        cout << "Error sending bytes." << endl;
    } else {
        #ifdef STREAMDEBUG
        cout << "sending succesfull" << endl;
        #endif
    }

    free(stream);
}
