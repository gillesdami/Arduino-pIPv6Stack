#include "PicoIPv6Connection.h"
#include "SerialDebugMACLayer.h"

uint8_t buf[UIP_BUFSIZE];
PicoIPv6Connection* connection;
SerialDebugMACLayer mac;

void setup() {
  if (!mac.init()){
    PRINTF("CANNOT INITIALIZE.. CANNOT CONTINUE");
    while (1){};
  }

  connection = new PicoIPv6Connection(&mac, buf);

  connection->connect();
  delay(200);
  Serial.println("SETUP!");
}

void loop() {
  if (connection->isConnected()){
    Serial.println("CONNECTED!");
    delay(100);

    
  } else {
    Serial.println("DISCONNECTED!");
    connection->connect();
  }
}

char msg_buf[160];

uint16_t msg_length;

void udp_input_callback(uint8_t* udp_data, uint16_t length){  
  uint8_t i;
  
  Serial.println("DATA rcv: ");
  for (i=0; i < length; ++i){
    Serial.print((char)udp_data[i], HEX);
  }
  
  for(i=0; i<length; ++i){
    msg_buf[length-1-i] = (char) udp_data[i]; 
  }
  
  msg_length = length;
}

