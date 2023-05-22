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
TEST(BCDNumTest0, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "10,8811881188");
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
TEST(BCDNumTest1, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "9,8910891089");
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
TEST(BCDNumTest2, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1");
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
TEST(BCDNumTest3, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1,0000258475");
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
TEST(BCDNumTest4, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "0,0007784338");
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
TEST(BCDNumTest5, DIV) {
	BCDNumber c = a / b;
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
TEST(BCDNumTest6, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "13,6084052797");
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
TEST(BCDNumTest7, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1,0000000138");
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
TEST(BCDNumTest8, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1,001001001");
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
TEST(BCDNumTest9, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "0,0037710762");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest10, ADD) {
	a = BCDNumber("3213214412,421414");
	b = BCDNumber("2141683252,6874623");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "5354897665,1088763");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest10, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "1071531159,7339517");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest10, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "6881687494376926900,3147018376922");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest10, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1,5003219586");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest11, ADD) {
	a = BCDNumber("3213214412642313213213213214215654654,42141454654654654645");
	b = BCDNumber("2141683252654654654654415162352165422,687462354654654654");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "5354897665296967867867628376567820077,10887690120120120045");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest11, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "1071531159987658558558798051863489231,73395219189189189245");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest11, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "6881687494744605046915986859868117475864060343695897209396904059293440634,0172999134256790214530836675611196783");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest11, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "1,5003219587");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest12, ADD) {
	a = BCDNumber("-321321441263213213214265468887542116546313213213213214215654654,42141454654654654645");
	b = BCDNumber("2141683252632132132132132154654621567822154654415162352165422,687462354654654654");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "-319179758010581081082133336732887494978491058558798051863489231,73395219189189189245");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest12, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-323463124515845345346397601042196738114135367867628376567820077,10887690120120120045");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest12, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "-688168749465043070211582078208917014591593928976554733415552861461407829672554749055165102862945704089809911467215564821009,0172999134256790214530836675611196783");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest12, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "-150,0321958759");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest13, ADD) {
	a = BCDNumber("-321321441263213213214265468887542116546313213213213214215654654,421414554564654654654654654654213544654654654645");
	b = BCDNumber("-21416832526321321322132132132132123132132154654621567822154654415162352165422,6874455765768768765432162354654654654");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "-21416832526321642643573395345345337397601042196738114135367867628376567820077,108860131141531531197870890119679010054654654645");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest13, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "21416832526321000000690868918918908866663267112505021508941441201948136510768,266031022012222221888561580811251920745345345355");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest13, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "6881687494650430702376351608041103817839343871772044657588632807019004479576428367425005320987150085708725839395899079578603120563029666677,585980494818003269867671616971620634218720445156368990268672149375144672675611196783");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest13, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest14, ADD) {
	a = BCDNumber("-32132144126321321321426548768756213123578768768887542116546313213213213214215654654,421414554564654654654654654654213544654654654645");
	b = BCDNumber("2141686587123857687654312872138732526321321322132132132132123132132154654621567822154654415162352165422,6874455765768768765432162354654654654");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "2141686587123857687622180728012411204999894773363375919008544363363267112505021508941441201948136510768,266031022012222221888561580811251920745345345355");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest14, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-2141686587123857687686445016265053847642747870900888345255701900901042196738114135367867628376567820077,108860131141531531197870890119679010054654654645");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest14, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "-68816982090873020597077625392671230269995668224788358712486811342556020261028508041965869790936357157124661400339381699203602255052078521450831098043969525199648140757394167875204002497,585980494818003269867671616971620634218720445156368990268672149375144672675611196783");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest14, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "-0");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest15, ADD) {
	a = BCDNumber("-32132144126321887879876345123784231387456432138765523213873887837321358773576546546213876354321321321426548768756213123578768768887542116546313213213213214215654654,421414554564654654654654654654213544654654654645");
	b = BCDNumber("214168658712385721323213213123123123123573543786978978645311387821321786876876513123877123687654312872138732526321321322132132132132123132132154654621567822154654415162352165422,6874455765768768765432162354654654654");
	BCDNumber c = a + b;
	EXPECT_EQ(c.toString(), "214168658712353589179086891235243246778449759555591522213172622298107912989039191765103547141108098995784411204999894773363375919008544363363267112505021508941441201948136510768,266031022012222221888561580811251920745345345355");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest15, SUB) {
	BCDNumber c = a - b;
	EXPECT_EQ(c.toString(), "-214168658712417853467339535011002999468697328018366435077450153344535660764713834482650700234200526748493053847642747870900888345255701900901042196738114135367867628376567820077,108860131141531531197870890119679010054654654645");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest15, MUL) {
	BCDNumber c = a * b;
	EXPECT_EQ(c.toString(), "-6881698209087421874350848764096369421035017838356428469568463431088524674489681472951569188649032031690605266622345590999882939595146179267797876344772569744983946257300356784518894071992369672127241188081161388959747158689514127534772499770288015975090580750676475669241656388930594095847396981795866955169525199648140757394167875204002497,585980494818003269867671616971620634218720445156368990268672149375144672675611196783");
	EXPECT_TRUE(true);
}
TEST(BCDNumTest15, DIV) {
	BCDNumber c = a / b;
	EXPECT_EQ(c.toString(), "-0");
	EXPECT_TRUE(true);
}
