#pragma once
#include <exception>
#include "FlashMemoryDevice.h"
#include <iostream>
using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
    const int EMPTY_VALUE = 0xFF;
};

class ReadFailException : public std::exception
{
public:
	explicit ReadFailException(char const* _Message)
		: exception(_Message)
	{
		cout << _Message << endl;
	}
};

class WriteFailException : public std::exception
{
public:
	explicit WriteFailException(char const* _Message)
		: exception(_Message)
	{
		cout << _Message << endl;
	}
};