#include <string>

#include "gtest/gtest.h"
#include "core/Buffer.h"

//-------------------------------------------------------------------

class CBufferTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
// 		m_Buf = new CBuffer(10);
	}
	virtual void TearDown()
	{
		delete m_Buf;
		m_Buf = nullptr;
	}

	CBuffer* m_Buf;
};

TEST_F(CBufferTest, testBufferWrite)
{
// 	EXPECT_EQ(m_Buf->Capacity(), 10);
// 	EXPECT_EQ(buffer.IsEmpty(), true);
// 	EXPECT_EQ(buffer.IsFull(), false);
// 	EXPECT_EQ(buffer.UsedCapacity(), 0);
// 	EXPECT_EQ(buffer.RemainedCapacity(), 10);

	std::string str("12345");
// 	buffer.Write(str.c_str(), str.length());


}

//-------------------------------------------------------------------


