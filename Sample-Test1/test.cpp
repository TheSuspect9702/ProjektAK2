#include "pch.h"
#include "../ProjektAK2/BCDNumber.cpp"
#include "../ProjektAK2/BCDNumber.h"
BCDNumber a = BCDNumber("1099");
BCDNumber b = BCDNumber("101");
TEST(BCDNumTest0, ADD) {
  BCDNumber c = a + b;
  EXPECT_EQ(c.toString(), "1200");
  EXPECT_TRUE(true);
}
TEST(BCDNumTest1, ADD) {
  a = BCDNumber("999");
  BCDNumber c = a + b;
  EXPECT_EQ(c.toString(), "1100");
  EXPECT_TRUE(true);
}
TEST(BCDNumTest2, SUB) {
	a = BCDNumber("1099");
	BCDNumber d = a - b;
	EXPECT_EQ(d.toString(), "998");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest3, SUB) {
	b = BCDNumber("1099");
	BCDNumber d = a - b;
	EXPECT_EQ(d.toString(), "0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest4, ADD) {
	a = BCDNumber("10992421645");
	b = BCDNumber("10992137525");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "21984559170");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest5, ADD) {
	a = BCDNumber("10992421645");
	b = BCDNumber("2");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "10992421647");
	EXPECT_TRUE(true);
}