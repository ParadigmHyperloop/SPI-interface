#include <iostream>
#include <sstream>
#include "bus/SPIDevice.h"

using namespace std;
using namespace exploringBB;

int main(){
   cout << "Starting EBB SPI ADC Example" << endl;
   SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(5000);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE1);
   busDevice->setBitsPerWord(16);
   unsigned char send[4], receive[4];
   // some documentation saying that you can only set more after the first 16 clock cycles
   send[0] = 0;          // This byte doesn't need to be set, just for a clear display
   send[1] = 0;          // This byte doesn't need to be set, just for a clear display
   // Send two bytes to initialize manual mode, choose Channel 0
   send[2] = 0b00000010;
   send[3] = 0b00000001;
   busDevice->transfer(send, receive, 4

);
   cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << "," << (int)receive[3] << "," << (int)receive[4] << endl;
   double lsb = 5/4096;
   // Getting values from the ADC
   while (true) {
     unsigned char send_cont[2], receive_cont[2];
     // I'm not sure if we should just send a blank signal or the same signal again to recieve values
     send[0] = 0b00000010;
     send[1] = 0b10000001; // The Start Bit followed

     busDevice->transfer(send_cont, receive_cont, 2);
     // Recieving 16 bits so bit shift the first value by 8 and then add the second to get the true value
     int value = ((int)receive_cont[0]<<8)|(int)receive_cont[1]);
     // print out the result
     cout << value << endl;
  }
}
