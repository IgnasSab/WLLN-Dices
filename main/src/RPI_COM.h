#ifndef RPI_COM_H
#define RPI_COM_h

#include <Arduino.h>

class RPI_COM {
    public:
        RPI_COM();
        void sendPacket();
        int receivePacket();
};

#endif
