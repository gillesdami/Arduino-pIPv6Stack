#include "PicoIPv6Connection.h"
#include "SerialDebugMACLayer.h"

u8_t buf[UIP_BUFSIZE];

SerialDebugMACLayer mac;
PicoIPv6Connection* connection;

void setup() {
  if (!mac.init()){
    PRINTF("CANNOT INITIALIZE.. CANNOT CONTINUE");
    while (1){};
  }

  connection = new PicoIPv6Connection(&mac, buf);
}

void loop() {
  // put your main code here, to run repeatedly:

}
