#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly    
    int cur_read = m_hardware->read(address);
    int prev_read = cur_read;
    for(int i =0; i < 4; ++i)
    {
        cur_read = m_hardware->read(address);
        if (cur_read != prev_read)
        {
            throw ReadFailException("READ FAIL!!!");
        }
        prev_read = cur_read;
    }

    return (int)cur_read;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}