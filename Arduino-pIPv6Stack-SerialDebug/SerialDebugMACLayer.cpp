#include "SerialDebugMACLayer.h"

bool SerialDebugMACLayer::init() {
    Serial.begin(9600);

    return true;
}

MACTransmissionStatus SerialDebugMACLayer::send(const uip_lladdr_t* lladdr_dest, uint8_t* data, uint16_t length, int* number_transmissions) {
    Serial.println("MAC ADDRESS DEST: 0x");
    for (int i=0; i<8; ++i) Serial.print(lladdr_dest->addr[i], HEX);

    Serial.print("\nMESSAGE LENGTH:");
    Serial.println(length, DEC);

    Serial.print("TRANSMISSIONS COUNT:");
    *number_transmissions = 1;
    Serial.println(*number_transmissions, DEC);

    Serial.print("DATA:");
    for (int i=0; i<length; ++i) {
        Serial.println(*(data+i), HEX);
        Serial.print(" ");
    }

    return MACTransmissionStatus::MAC_TX_STATUS_OK;
}

bool SerialDebugMACLayer::receive(uip_lladdr_t* lladdr_src, uip_lladdr_t* lladdr_dest, uint8_t* data, uint16_t* length) {
    uint8_t inChar = (uint8_t)"\n";
    *length = 0;

    Serial.println("\nRECEIVING:");

    do {
        while (Serial.available()) {
            *(data + *length) = (uint8_t)Serial.read();
            *length++;

            Serial.print(*(data + *length), HEX);
            Serial.print(" ");
        }
    } while (inChar != (uint8_t)"\n");

    if (*length == 0) {
        Serial.println("*Nothing*");
        return false;
    }

    //fake distant MAC
    for (int i=8; i>0; --i) lladdr_src->addr[i] = i;

    //fake MAC dest
    for (int i=0; i<8; ++i) lladdr_dest->addr[i] = i;

    Serial.println("RECEIVED FROM MAC ADDRESS: 0x");
    for (int i=0; i<8; ++i) Serial.print(lladdr_src->addr[i], HEX);

    Serial.println("\nMAC ADDRESS DEST: 0x");
    for (int i=0; i<8; ++i) Serial.print(lladdr_dest->addr[i], HEX);

    Serial.println("\nDATA LENGTH:");
    Serial.println(*length, DEC);

    Serial.println("\nDATA:");
    for (int i=0; i<*length; ++i) {
        Serial.println(*(data+i), HEX);
        Serial.print(" ");
    }
    
    const uip_lladdr_t* selfAddress = getMacAddress();
    for (int i=0; i<8; ++i) {
        if(lladdr_dest->addr[i] != selfAddress->addr[i]) {
            Serial.println("\nWe are NOT the recipient !");
            return false;
        }
    }

    Serial.println("\nWe are the recipient !");
    return true;
}

const uip_lladdr_t* SerialDebugMACLayer::getMacAddress() {
    uip_lladdr_t* selfAddress = new uip_lladdr_t();

    for (int i=0; i<8; ++i) selfAddress->addr[i] = i;

    Serial.println("SELF MAC ADDRESS: 0x");
    for (int i=0; i<8; ++i) Serial.print(selfAddress->addr[i], HEX);

    return selfAddress;
}