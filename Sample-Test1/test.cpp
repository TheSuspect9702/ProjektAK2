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
TEST(BCDNumTest0, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "998");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest0, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "110999");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest1, ADD) {
  a = BCDNumber("999");
  BCDNumber c = a + b;
  EXPECT_EQ(c.toString(), "1100");
  EXPECT_TRUE(true);
}
TEST(BCDNumTest1, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "898");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest1, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "100899");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest2, ADD) {
	a = BCDNumber("1099");
	b = BCDNumber("1099");
	BCDNumber d = a + b;
	EXPECT_EQ(d.toString(), "2198");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest2, SUB) {
	BCDNumber d = a - b;
	EXPECT_EQ(d.toString(), "0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest2, MUL) {
	BCDNumber d = a * b;
	EXPECT_EQ(d.toString(), "1207801");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest3, ADD) {
	a = BCDNumber("10992421645");
	b = BCDNumber("10992137525");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "21984559170");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest3, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "284120");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest3, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "120830210454626728625");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest4, ADD) {
	a = BCDNumber("21546");
	b = BCDNumber("27678652");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "27700198");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest4, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-27657106");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest4, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "596364235992");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest5, ADD) {
	a = BCDNumber("0");
	b = BCDNumber("8420");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "8420");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest5, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-8420");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest5, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest6, ADD) {
	a = BCDNumber("-875312387");
	b = BCDNumber("-64321452");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "-939633839");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest6, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-810990935");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest6, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "56301363685425924");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest7, ADD) {
	a = BCDNumber("21562554526325");
	b = BCDNumber("21562554228522");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "43125108754847");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest7, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "297803");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest7, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "464943751279345319514841650");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest8, ADD) {
	a = BCDNumber("1000");
	b = BCDNumber("999");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "1999");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest8, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "1");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest8, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "999000");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest9, ADD) {
	a = BCDNumber("121399218");
	b = BCDNumber("32192193712");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "32313592930");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest9, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-32070794494");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest9, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "3908107142341317216");
	EXPECT_TRUE(true);
}