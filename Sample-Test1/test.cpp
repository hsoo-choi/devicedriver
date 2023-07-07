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