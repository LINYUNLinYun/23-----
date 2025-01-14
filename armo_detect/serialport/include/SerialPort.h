/*
 * 	串口通讯
 */
#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class SerialPort {
private:
	pthread_t listen_thread;
public:
	enum BaudRate {
		BR0 = 0000000,
		BR50 = 0000001,
		BR75 = 0000002,
		BR110 = 0000003,
		BR134 = 0000004,
		BR150 = 0000005,
		BR200 = 0000006,
		BR300 = 0000007,
		BR600 = 0000010,
		BR1200 = 0000011,
		BR1800 = 0000012,
		BR2400 = 0000013,
		BR4800 = 0000014,
		BR9600 = 0000015,
		BR19200 = 0000016,
		BR38400 = 0000017,
		BR57600 = 0010001,
		BR115200 = 0010002,
		BR230400 = 0010003,
		BR460800 = 0010004,
		BR500000 = 0010005,
		BR576000 = 0010006,
		BR921600 = 0010007,
		BR1000000 = 0010010,
		BR1152000 = 0010011,
		BR1500000 = 0010012,
		BR2000000 = 0010013,
		BR2500000 = 0010014,
		BR3000000 = 0010015,
		BR3500000 = 0010016,
		BR4000000 = 0010017
	};
	enum DataBits {
		DataBits7, DataBits8
	};
	enum StopBits {
		StopBits1, StopBits2
	};
	enum Parity {
		ParityNone, ParityEven, ParityOdd,
	};
	int fd;
	struct Config_t {
		char *DevicePath;
		enum BaudRate BaudRate;
		enum DataBits DataBits;
		enum StopBits StopBits;
		enum Parity Parity;
	} Config;
	/**
	 * @brief 串口打开函数
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Open();
	void Close();
	bool LoadConfig();	
	bool Send(unsigned char byte);
	bool Send(std::vector<unsigned char> data);
	bool Send(char *data, unsigned int len);
	bool SerialPort_init(SerialPort &UART);
	std::vector<unsigned char> SendMessageChange(int angleX,int angleY);
};

/*
* 这个地方使用起来要特别注意！
* 运算符重载，支持３种输入类型：unsigned char,vector<unsigned char>,char*。
* 不过使用容器发送偶有错误，建议谨慎使用！
*/

bool operator <<(SerialPort port, std::vector<unsigned char> data);
bool operator <<(SerialPort port, unsigned char byte);
bool operator <<(SerialPort port, char const *data);
