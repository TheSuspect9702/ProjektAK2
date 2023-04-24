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
TEST(BCDNumTest6, MUL) {
	a = BCDNumber("0");
	b = BCDNumber("8420");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest7, MUL) {
	a = BCDNumber("99");
	b = BCDNumber("99");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "9801");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest8, MUL) {
	a = BCDNumber("8");
	b = BCDNumber("7");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "56");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest9, MUL) {
	a = BCDNumber("123");
	b = BCDNumber("6");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "738");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest10, MUL) {
	a = BCDNumber("999");
	b = BCDNumber("99");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "98901");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest11, MUL) {
	a = BCDNumber("100");
	b = BCDNumber("100");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "10000");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest12, MUL) {
	a = BCDNumber("5");
	b = BCDNumber("120");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "600");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest13, MUL) {
	a = BCDNumber("25649");
	b = BCDNumber("64273");
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "1648538177");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest14, SUB) {
	a = BCDNumber("25649");
	b = BCDNumber("64273");
	BCDNumber c = b - a;
	EXPECT_EQ(c.toString(), "38624");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest15, SUB) {
	a = BCDNumber("254496");
	b = BCDNumber("245393");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "9103");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest16, SUB) {
	a = BCDNumber("21562554526325");
	b = BCDNumber("21562554228522");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "297803");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest17, SUB) {
	a = BCDNumber("1000");
	b = BCDNumber("999");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "1");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest18, SUB) {
	a = BCDNumber("1000");
	b = BCDNumber("9");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "991");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest19, SUB) {
	a = BCDNumber("5559");
	b = BCDNumber("4999");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "560");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest20, SUB) {
	a = BCDNumber("10101010");
	b = BCDNumber("1010101");
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "9090909");
	EXPECT_TRUE(true);
}