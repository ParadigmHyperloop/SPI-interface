/* Using an SPI ADC (e.g., the MCP3008)
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include <sstream>
#include "bus/SPIDevice.h"
#include <unistd.h>

using namespace std;
using namespace exploringBB;

short combineValues(unsigned char upper, unsigned char lower){
   return ((short)upper<<8)|(short)lower;
}

int main(){
   cout << "Starting EBB SPI ADC Example" << endl;
   SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   //SPIDevice *busDeviceTwo = new SPIDevice(2,1); //Using second SPI bus (both loaded)
   busDevice->setSpeed(2500);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE2);
   busDevice->setBitsPerWord(16);
	
	/*
   busDeviceTwo->setSpeed(2500);      // Have access to SPI Device object
   busDeviceTwo->setMode(SPIDevice::MODE2);
   busDeviceTwo->setBitsPerWord(16);
	*/
	
   unsigned char send[2], receive[2];
   //send[0] = 0;          // This byte doesn't need to be set, just for a clear display
   //send[1] = 0;          // This byte doesn't need to be set, just for a clear display
   send[0] = 0b11000000; // The Start Bit followed
   send[1] = 0b00011011;

   // Set the SGL/Diff and D mode -- e.g., 1000 means single ended CH0 value
   //busDeviceTwo->transfer(send, receive, 2);
   //busDeviceTwo->transfer(send, receive, 2);
   busDevice->transfer(send, receive, 2);
   busDevice->transfer(send, receive, 2);
   cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << endl;
   double lsb = 5/4096;
   for (int i = 0; i <= 1000; i++) {
     unsigned char send[2], recieve[2];
     send[0] = 0b11000000; // The Start Bit followed
     send[1] = 0b00011011;
     busDevice->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000) >>4;
     cout << "Channel: " << channel << " Value: " << value << endl;
	 //usleep(1000000);
   }
   
   /*
   for (int i = 0; i <= 100; i++) {
     unsigned char send[2], recieve[2];
     send[0] = 0b00000000;
     send[1] = 0b00000000; // The Start Bit followed
     busDevice->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000)>>4;
     cout << "Channel: " << channel << " Value: " << value << endl;
   }
   cout << "Switching to Channel 0" << endl;
   cout << "Sleeping" << endl;
   //usleep(1000000);
   for (int i = 0; i <= 1000; i++) {
     unsigned char send[2], recieve[2];
     send[0] = 0b00000000; // The Start Bit followed
     send[1] = 0b00010000;
     busDevice->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000)>>4;
     cout << "Channel: " << channel << " Value: "<< value << endl;
   }
   cout << "Switching to Channel 1" << endl;
   for (int i = 0; i <= 2000; i++) {
     unsigned char send[2], recieve[2];
     send[0] = 0b10000000; // The Start Bit followed
     send[1] = 0b00010000;
     busDevice->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000)>>4;
     cout << "ADC1 -- Channel: " << channel << " Value: "<< value << endl;
   }
   cout << "Switching to ADC 2 Channel 3" << endl;
   for (int i = 0; i <= 2000; i++) {
     unsigned char send[2], recieve[2];
     send[0] = 0b10000000; // The Start Bit followed
     send[1] = 0b00010001;
     busDeviceTwo->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000)>>4;
     cout << "ADC2 -- Channel: " << channel << " Value: "<< value << endl;
   }
   
   cout << "Infinite loop!" << endl;
   while (true) {
     unsigned char send[2], recieve[2];
     send[0] = 0b00000000;
     send[1] = 0b00000000; // The Start Bit followed
     busDevice->transfer(send, recieve, 2);
     int value = (((int) recieve[1] & 0b00001111)<<8)|(int)recieve[0];
     int channel = ((int) recieve[1] & 0b11110000)>>4;
     cout << "Channel: " << channel << " Value: "<<  value << endl;
   }*/
}
