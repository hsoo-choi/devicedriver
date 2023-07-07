#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;
using namespace std;

#include "../DeviceDriver/DeviceDriver.cpp"

class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long adress, unsigned char data), (override));
};

class TestFixture : public testing::Test
{
public:
	MockDevice md;
	DeviceDriver *dd;

	void assertIllegalRead(long address)
	{
		try
		{
			dd->read(address);
			FAIL();
		}
		catch(ReadFailException e)
		{
		}
	}
	void assertIllegalWrite(long address, int data)
	{
		try
		{
			dd->write(address, data);
			FAIL();
		}
		catch (WriteFailException e)
		{
		}
	}
protected:
	void SetUp() override
	{
		dd = new DeviceDriver(&md);
	}
};

TEST_F(TestFixture, ReadTestPass) {
	EXPECT_CALL(md, read)
		.Times(5)
		.WillRepeatedly(Return(10));		

	EXPECT_EQ(10, dd->read(0xA));
}

TEST_F(TestFixture, ReadTestFailWithException) {
	EXPECT_CALL(md, read)
		.WillOnce(Return(10))
		.WillOnce(Return(10))
		.WillOnce(Return(10))
		.WillOnce(Return(10))
		.WillOnce(Return(20));

	assertIllegalRead(0xA);
}

TEST_F(TestFixture, WriteTestPass) {
	EXPECT_CALL(md, read).WillOnce(Return(0xFF));
	EXPECT_CALL(md, write).Times(1);

	dd->write(0xA, 1000);
}

TEST_F(TestFixture, WriteTestFailWithException) {
	EXPECT_CALL(md, read).WillOnce(Return(10));

	assertIllegalWrite(0xA, 1000);
}
