#include "EndianHelper.h"
#include "gtest/gtest.h"

TEST(EndianHelper, IntelIsLittleEndian) {
	EXPECT_TRUE(Serial::isLittleEndian());
}