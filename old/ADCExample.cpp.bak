/* Using an SPI ADC (e.g., the MCP3008)
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include <sstream>
#include "bus/SPIDevice.h"

using namespace std;
using namespace exploringBB;

short combineValues(unsigned char upper, unsigned char lower){
   return ((short)upper<<8)|(short)lower;
}

int main(){
   cout << "Starting EBB SPI ADC Example" << endl;
   SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(2500);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE1);
   busDevice->setBitsPerWord(16);
   unsigned char send[2], receive[2];
   //send[0] = 0;          // This byte doesn't need to be set, just for a clear display
   //send[1] = 0;          // This byte doesn't need to be set, just for a clear display
   send[0] = 0b00011000;
   send[1] = 0b10000000; // The Start Bit followed

   // Set the SGL/Diff and D mode -- e.g., 1000 means single ended CH0 value
   //send[1] = 0b01000000; // The MSB is the Single/Diff bit and it is followed by 000 for CH0
   busDevice->transfer(send, receive, 2);
   cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << "," << (int)receive[3] << "," << (int)receive[4] << endl;
   double lsb = 5/4096;
   while (true) {
     unsigned char send_cont[2], receive_cont[2];
     send[0] = 0b00010000;
     send[1] = 0b10000000; // The Start Bit followed
     //cout << "IN ADC " << hex << (unsigned long) send << endl;
     busDevice->transfer(send_cont, receive_cont, 2);
     int value = ((int) receive_cont[1] & 0b00001111) << 8;
     value += (int)receive_cont[0];
     cout << value << endl;
     /*for (int i=0;i<=20; i = i+2) {
         //cout << (double)(5/(int)receive_cont[i]) << " V" << endl;
         msb = 
         cout << (int)receive_cont[i] << " V" << endl;
     }*/
  }
  // cout << "Response bytes are " << (int)receive << ","<< endl;

   // Use the 8-bits of the second value and the two LSBs of the first value
   //int value = recieve //combineValues(receive[1]&0b00000011, receive[2]);
   //cout << "This is the value " << value << " out of 1024." << endl;
   //cout << "End of EBB SPI ADC Example" << endl;
}
