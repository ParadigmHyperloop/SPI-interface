// SPI Library
#include "bus/SPIDevice.h"

// Basic Libraries
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Key Pressed Libraries
#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>

using namespace std;
using namespace exploringBB;

// Convert int/double to a string
string convert(double number){
	ostringstream strs;
	strs << number;
	return strs.str();
}

// Check if a key has been pressed
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int main(){
	
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
	send[0] = 0b01000000;
	send[1] = 0b00011000; // The Start Bit followed
	busDevice->transfer(send, receive, 2);
	cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << "," << (int)receive[3] << "," << (int)receive[4] << endl;
	int value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
	int channel = ((int) receive[1] & 0b11110000) >>4;
	double voltage = 0;
	usleep(1000000);
	cout << "\033[2J\033[1;1H";
	
	while(!_kbhit()) {
		
		vector<string> lines;
		
		lines.push_back("=== ADC Monitor - SPI1 Bus - Device 0 ===\n\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011001;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011001;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011010;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011010;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011011;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011011;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011100;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011100;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011101;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011101;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011110;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011110;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011111;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011111;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b01000000;
		send[1] = 0b00011000;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		send[0] = 0b11000000;
		send[1] = 0b00011000;
		busDevice->transfer(send, receive, 2);
		value = (((int) receive[1] & 0b00001111)<<8)|(int)receive[0];
		channel = ((int) receive[1] & 0b11110000) >>4;
		voltage = value*0.0012207;
		lines.push_back("Channel: " + convert(channel) + ", Value: " + convert(value) + ", Voltage: " + convert(voltage) + "V\n");
		
		lines.push_back("\nPress Any Key to Exit.\n");
		
		// Write Lines to screen
		for(int j=0; j<lines.size(); j++){
			cout << lines[j];
		}
		
		// Wait 1 second then clear screen
		usleep(1000000);
		cout << "\033[2J\033[1;1H";
	}
	
}