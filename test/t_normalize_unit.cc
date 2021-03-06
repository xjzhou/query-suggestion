/*************************************************************************
 @ File Name: t_normalize_unit.cc
 @ Method: 
 @ Author: Jerry Shi
 @ Mail: jerryshi0110@gmail.com
 @ Created Time: Tue 12 Jul 2016 05:30:00 PM CST
 ************************************************************************/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE normalizeTest
//#include <boost/test/unit_test.hpp>
#include <iostream>
#include "unit_test.h"
#include "util/normalize.h"

// name of the test suite is normalizeTest
BOOST_AUTO_TEST_SUITE (normalizeTest)

// 1 Normalize::ToLower()
// Convert string to lower case
BOOST_AUTO_TEST_CASE (ToLower) {
    std::string str("ABCD-HK.3SG");
    Normalize::ToLower(str);
    BOOST_CHECK_MESSAGE(str == "abcd-hk.3sg", "ToLower result: " << str);
}

// 2 Normalize::ToUpper()
// Convert string to upper case
BOOST_AUTO_TEST_CASE (ToUpper) {
    std::string str("i love you 小红!");
    Normalize::ToUpper(str);
    BOOST_CHECK_MESSAGE(str == "I LOVE YOU 小红!", "ToUpper result: " << str);
}

// 3 Normalize::ToUTF8()
// Convert to utf8 encoding
BOOST_AUTO_TEST_CASE (UTF8Encoding) {
    std::string str("a\x80\xe0\xa0\xc0\xaf\xed\xa0\x80z");
    Normalize::ToUTF8(str);
    BOOST_CHECK_MESSAGE(str == "a����z", "To utf8 result:" << str);
    str = "把";
   // Normalize::ToUTF8(str);
   // std::cout << "T: " << str << "\t T[0]:" << tt << std::endl;
}

// 4 Normalize::IsValidUTF8()
// Check a string is a valid utf8 encoding
BOOST_AUTO_TEST_CASE (IsUTF8Encoding) {
    // unknown encoding 日ш
    std::string str("\xe6\x97\xa5\xd1\x88\xfa");
    bool flag = Normalize::IsValidUTF8(str);
    BOOST_CHECK_MESSAGE(flag == false, "IsUTF8Encoding result: " << flag);
}

// 5 Normalize::IsChinese()
// Determine whether a string is a chinese characters
BOOST_AUTO_TEST_CASE (IsChinese) {
    // not chinese as it contains "》"
    std::string str("我爱中国》");
    bool flag = Normalize::IsChinese(str);
    BOOST_CHECK_MESSAGE( flag == false, str << "IsChinese result: " << flag);
    str = "青青原上草";
    flag = Normalize::IsChinese(str);
    BOOST_CHECK_MESSAGE( flag == true, str << " IsChinese result: " << flag);
}

// 6 Normalize::ToUnicode()
// Get utf16 encoding arrary of a string
BOOST_AUTO_TEST_CASE (ToUnicode) {
    std::string str("大智若愚");
    std::vector<uint16_t> unicodes;
    Normalize::ToUnicode(str, unicodes);
    BOOST_CHECK_MESSAGE( unicodes.size() == 4, str << "To utf16 size: " << unicodes.size());
    
    str = "银行abc";
    Normalize::ToUnicode(str, unicodes);
    BOOST_CHECK_MESSAGE( unicodes.size() == 5, str << "To utf16 size: " << unicodes.size());
}

// 7 Normalize::UnicodeToUTF8Str()
// Convert a chinese character with utf16 encoding(uint16_t) to a utf8 string
BOOST_AUTO_TEST_CASE (UnicodesToUTF8Str) {
    std::string str("中华人民共和国");
    std::vector<uint16_t> unicodes;
    Normalize::ToUnicode(str, unicodes);
    std::string utf8str;
    Normalize::UnicodeToUTF8Str(unicodes, utf8str);
    BOOST_CHECK_MESSAGE( str == utf8str, str << "After utf16 encoding and decoding: " << utf8str);
    
    str = "连衣裙Love";
    Normalize::ToUnicode(str, unicodes);
    Normalize::UnicodeToUTF8Str(unicodes, utf8str);
    BOOST_CHECK_MESSAGE( str == utf8str, str << "After utf16 encoding and decoding: " << utf8str);
}

// 8 Normalize::UnicodeToUTF8Str()
// Convert a chinese character with utf16 encoding(uint16_t) to a utf8 string
BOOST_AUTO_TEST_CASE (UnicodeToUTF8Str) {
    std::string str("爱");
    std::vector<uint16_t> unicodes;
    Normalize::ToUnicode(str, unicodes);
    std::string utf8str;
    Normalize::UnicodeToUTF8Str(unicodes[0], utf8str);
    BOOST_CHECK_MESSAGE( str == utf8str, str << "After utf16 encoding and decoding: " << utf8str);
}

// 9 Normalize::IsDigit()
BOOST_AUTO_TEST_CASE (IsDigit) {
    bool flag = false;
   flag =  Normalize::IsDigit('2');
   BOOST_CHECK_MESSAGE( flag == true, "'s' IsDigit result: " << flag);

   flag = Normalize::IsDigit('w');
   BOOST_CHECK_MESSAGE(flag == false, "'w' IsDigit result: " << flag);
}

// 10 Normalize::IsAlpha()
BOOST_AUTO_TEST_CASE (IsAlpha) {
   bool flag = false;
   flag =  Normalize::IsAlpha('z');
   BOOST_CHECK_MESSAGE( flag == true, "'z' IsDigit result: " << flag);

   flag = Normalize::IsAlpha('3');
   BOOST_CHECK_MESSAGE(flag == false, "'3' IsDigit result: " << flag);
}

// 11 Normalize::IsConnector()
BOOST_AUTO_TEST_CASE (IsConnector) {
   bool flag = false;
   flag =  Normalize::IsConnector('-');
   BOOST_CHECK_MESSAGE( flag == true, "'-' IsDigit result: " << flag);

   flag = Normalize::IsConnector('.');
   BOOST_CHECK_MESSAGE(flag == true, "'.' IsDigit result: " << flag);
   
   flag = Normalize::IsConnector('+');
   BOOST_CHECK_MESSAGE(flag == true, "'+' IsDigit result: " << flag);
   
   flag = Normalize::IsConnector('=');
   BOOST_CHECK_MESSAGE(flag == false, "'=' IsDigit result: " << flag);
}

// 12 Normalize::IsBreakPunct()
BOOST_AUTO_TEST_CASE (IsPunct) {
   bool flag = false;
   flag =  Normalize::IsBreakPunct('[');
   BOOST_CHECK_MESSAGE( flag == true, "'[' IsDigit result: " << flag);

   flag = Normalize::IsBreakPunct(']');
   BOOST_CHECK_MESSAGE(flag == true, "']' IsDigit result: " << flag);
   
   flag = Normalize::IsBreakPunct('(');
   BOOST_CHECK_MESSAGE(flag == true, "'(' IsDigit result: " << flag);
   
   flag = Normalize::IsBreakPunct(')');
   BOOST_CHECK_MESSAGE(flag == true, "')' IsDigit result: " << flag);
   
   flag = Normalize::IsBreakPunct('{');
   BOOST_CHECK_MESSAGE(flag == true, "'{' IsDigit result: " << flag);
   
   flag = Normalize::IsBreakPunct('}');
   BOOST_CHECK_MESSAGE(flag == true, "'}' IsDigit result: " << flag);
   
   flag = Normalize::IsBreakPunct('*');
   BOOST_CHECK_MESSAGE(flag == false, "'*' IsDigit result: " << flag);
}

// 13 Normalize::IsPunctuation()
BOOST_AUTO_TEST_CASE (IsPunctuation) {
   bool flag = false;
   flag =  Normalize::IsPunctuation('[');
   BOOST_CHECK_MESSAGE( flag == true, "'[' IsDigit result: " << flag);
   
   flag =  Normalize::IsPunctuation(',');
   BOOST_CHECK_MESSAGE( flag == true, "',' IsDigit result: " << flag);
   
   flag =  Normalize::IsPunctuation('?');
   BOOST_CHECK_MESSAGE( flag == true, "'?' IsDigit result: " << flag);
}

BOOST_AUTO_TEST_SUITE_END()


