#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int cur_read = m_hardware->read(address);
    int prev_read = cur_read;
    int cnt = 4;
    while(cnt--)
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
    int cur_read = m_hardware->read(address);
    if(cur_read != EMPTY_VALUE)
    {
        throw WriteFailException("WRITE FAIL!!");
    }
    m_hardware->write(address, (unsigned char)data);
}