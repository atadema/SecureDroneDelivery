# SecureDroneDelivery
Reliable and secure payload authentication for (semi-) autonomous drone delivery

This repository contains the following three independently operating codebases. They tie in together to form a software system that allows for the reliable and secure communication between the Controller and payload container that is transported by a (semi-) autonomous drone.

1. Chirpstack LoRa Application Server (dockerfile)
2. Node-RED authentication flow for the secure authentication of the recipient of the payload container (dockerfile)
3. Arduino C++ file + dependencies for Arduino M0 microcontroller with RN2483 LoRaWAN module (Arduino IDE .ino C++ files + dependencies)
4. Mosquitto MQTT Broker (Pushes the data received by Wanesy LoRa Network Server to the ChirpStack LoRa Application Server. 
