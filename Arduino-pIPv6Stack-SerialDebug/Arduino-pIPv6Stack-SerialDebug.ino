#include "PicoIPv6Connection.h"
#include "SerialDebugMACLayer.h"

uint8_t buf[UIP_BUFSIZE];
SerialDebugMACLayer mac;
PicoIPv6Connection *connection;

void setup() {
  if (!mac.init()){
    PRINTF("CANNOT INITIALIZE.. CANNOT CONTINUE");
    while (1){};
  }

  uip_lladdr_t* selfAddress = new uip_lladdr_t();
  for (int i=1; i<9; ++i) selfAddress->addr[i] = i;
  mac.setMacAddress(selfAddress);

  connection = new PicoIPv6Connection(&mac, buf);

  delay(200);
  Serial.println("SETUP!");
}

void loop() {
  if (connection->isConnected()){
    Serial.println("CONNECTED!");
    delay(100);
    uip_ipaddr_t* ip_destination_address   = connection->getLastSenderIPAddress();   // Get Last Sender's IP Address.
    connection->udp_send(ip_destination_address , 8765, 8765, "hi", 3 );
    delay(100);
    
  } else {
    Serial.println("DISCONNECTED!");
    connection->connect();
    delay(200);
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

