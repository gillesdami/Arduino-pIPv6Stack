Arduino pico IPv6 stack
=======================

A very light IPv6 stack for [Arduinos](http://www.arduino.cc/) UNO over bluetooth based on [Contiki OS](http://www.contiki-os.org/) network stack.

- Coap
- UDP
- 6LowPAN / RPL
- Device Address

Features
--------

* IP network stack with low-power standards : [6LoWPAN](http://datatracker.ietf.org/wg/6lowpan/charter/), reduced [RPL](http://tools.ietf.org/html/rfc6550), and [CoAP](http://datatracker.ietf.org/doc/draft-ietf-core-coap/)
* Compatible with all [Arduino](http://arduino.cc/en/Main/Products) boards 
* Based on [Contiki OS](http://www.contiki-os.org/) network stack

Get Started
-----------

Link your arduino with an HC-05 module and start sending/receiving data through CoAPEngine or PicoIPv6Connection.
For xbee modules check the parent repository, for other modules you can implement your own MACLayer.

License
-------
 
MIT