#ifndef __SERIALDEBUGMACLAYER_H__
#define __SERIALDEBUGMACLAYER_H__

#include "MACLayer.h"
#include <HardwareSerial.h>

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


class nRFMACLayer : public MACLayer {
    private:
    uip_lladdr_t* selfMacAddress;
    RF24 radio;

    public:
    void setMacAddress(uip_lladdr_t* selfMacAddress) {
        this->selfMacAddress = selfMacAddress;
    };

    //********************************************************************************************************//
	/*____function init(): Initializes the MAC Layer. Must be called before performing any other operation.
	 *
	 * 	____In:  void
	 * 	____Out: boolean: 	true--  MAC Layer was correctly initialized. Can utilize getMacAddress, send and receive commands
	 * 			    		false-- MAC Layer was not properly initialized. Error ocurred and we must not continue.
	 */
	bool init();
	//********************************************************************************************************//

	//********************************************************************************************************//
	/*____function send: Sends a MAC frame
	 *	____In: const uip_lladdr_t* lladdr_dest: MAC@ of the destination (Broadcast will be represented by an all-zeroes address)
	 *	    	uint8_t* data: 		     		 (a pointer to) the data to send
	 *        	uint16_t length: 		     	 the size of the data (in bytes)
	 *        	int* number_transmissions: 	     The pointed address will be filled with the total number of
	 *        										MAC layer transmissions that were performed (1 or more).
	 *
	 *	____Out: MACTransmissionStatus: return the status of the MACLayer defined at the beginning of this class
	 */
    MACTransmissionStatus send(const uip_lladdr_t* lladdr_dest, uint8_t* data, uint16_t length, int* number_transmissions);
	//********************************************************************************************************//

    //********************************************************************************************************//
    /*____function receive : Polls the MAC layer to see if it received a new MAC frame/packet.
     *			 				If new packet (to myself or multicast/bcast):	Use the packet, return true;
     *			 				No new packet:    								Do nothing, return false.
     *
     *____In:   uip_lladdr_t* lladdr_src: (MUST point to a valid uip_lladdr_t variable -with reserved memory-). If we receive
     *									  a new packet, pointed destination will be filled with the sender's MAC@.
     *
     *	    	uip_lladdr_t* lladdr_dest: (If new packet arrived)
     *	    							   If destination MAC@ is Broadcast,  uip_lladdr_t* lladdr_dest pointer will point to a uip_lladdr_t with all ZEROES
     *
     *	    							   If packet is for myself (unicast)  uip_lladdr_t* lladdr_dest pointer will point to a uip_lladdr_t variable with my MAC@.
     *
     *	    	uint8_t* data: 	 Pointer to where the received data will be copied (if a new packet arrived).
     *
     *          uint16_t* length: The pointed address will be filled with the length (in bytes) of the new data.
     *
     *____Out: boolean : true--  packet for myself, and store the dst and src MAC@
     *				     false-- packet for someone else
     */
    bool receive(uip_lladdr_t* lladdr_src, uip_lladdr_t* lladdr_dest, uint8_t* data, uint16_t* length);
	//********************************************************************************************************//

    //********************************************************************************************************//
    /*___________________function getMAcAdress: return the MAC@ address of the MAC Layer
     *___________________In:void
     *
     *___________________Out: uip_lladdr_t*:  Pointer to a uip_lladdr_t with my MAC Address.
     */
    const uip_lladdr_t* getMacAddress();
	//********************************************************************************************************//
};

#endif /* __SERIALDEBUGMACLAYER_H__ */