// SPI Library
#include "bus/SPIDevice.h"

// Basic Libraries
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace exploringBB;

int main(int argc, char* argv[]){
	
	// Init BBB SPI1 Bus
	cout << "Initializing BBB SPI1 Bus..." << endl;
	SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
	busDevice->setSpeed(2500);      // Have access to SPI Device object
	busDevice->setMode(SPIDevice::MODE2);
	busDevice->setBitsPerWord(16);
	cout << "Initialize Complete." << endl;

	// Init Send and Receive Variables
	cout << "Test ADC Response..." << endl;
	unsigned char send[2], receive[2];
	
	if(std::string(argv[1]) == "0") {
		send[0] = 0b01000000;
		send[1] = 0b00011000;
	} 
	else if(std::string(argv[1]) == "1") {
		send[0] = 0b11000000;
		send[1] = 0b00011000;
	}
	else if(std::string(argv[1]) == "2") {
		send[0] = 0b01000000;
		send[1] = 0b00011001;
	}
	else if(std::string(argv[1]) == "3") {
		send[0] = 0b11000000;
		send[1] = 0b00011001;
	}
	else if(std::string(argv[1]) == "4") {
		send[0] = 0b01000000;
		send[1] = 0b00011010;
	}
	else if(std::string(argv[1]) == "5") {
		send[0] = 0b11000000;
		send[1] = 0b00011010;
	}
	else if(std::string(argv[1]) == "6") {
		send[0] = 0b01000000;
		send[1] = 0b00011011;
	}
	else if(std::string(argv[1]) == "7") {
		send[0] = 0b11000000;
		send[1] = 0b00011011;
	}
	else if(std::string(argv[1]) == "8") {
		send[0] = 0b01000000;
		send[1] = 0b00011100;
	}
	else if(std::string(argv[1]) == "9") {
		send[0] = 0b11000000;
		send[1] = 0b00011100;
	}
	else if(std::string(argv[1]) == "10") {
		send[0] = 0b01000000;
		send[1] = 0b00011101;
	}
	else if(std::string(argv[1]) == "11") {
		send[0] = 0b11000000;
		send[1] = 0b00011101;
	}
	else if(std::string(argv[1]) == "12") {
		send[0] = 0b01000000;
		send[1] = 0b00011110;
	}
	else if(std::string(argv[1]) == "13") {
		send[0] = 0b11000000;
		send[1] = 0b00011110;
	}
	else if(std::string(argv[1]) == "14") {
		send[0] = 0b01000000;
		send[1] = 0b00011111;
	}
	else {
		send[0] = 0b11000000;
		send[1] = 0b00011111;
	}
	
	busDevice->transfer(send, receive, 2);
	busDevice->transfer(send, receive, 2);
	busDevice->transfer(send, receive, 2);
	cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << "," << (int)receive[3] << "," << (int)receive[4] << endl;
	int value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
	int channel = ((int) receive[1] & 0b11110000) >>4;
	double voltage = 0;
	usleep(1000000);
	cout << "\033[2J\033[1;1H";
		
	cout << "=== ADC Test - Channel " << argv[1] << " ===\n\n";
	
	for(int i = 0; i<10; i++) {
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		cout << value << "     " << voltage << "\n";
		
		// Wait 1 second then clear screen
		usleep(100000);
	}
	
	cout << "\n";
}