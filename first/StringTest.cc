
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "String.hh"

using Axurez::String;
using Axurez::Order;

int main() {
  String string("hahaa");

  String string1 = "heiheihei";

  switch (string.compareWith(string1)) {
    case Order::GREATER:
      printf("%s bigger than %s\n", string.cStr(), string1.cStr());
      break;
    case Order::EQUAL:
      printf("%s equal to %s\n", string.cStr(), string1.cStr());
      break;
    case Order::SMALLER:
      printf("%s smaller than %s\n", string.cStr(), string1.cStr());
      break;
  }

  assert(String("a").compareWith(String("b")) == Order::SMALLER);
  assert(String("aa").compareWith(String("b")) == Order::SMALLER);
  assert(String("a").compareWith(String("ab")) == Order::SMALLER);
  assert(String("ab").compareWith(String("a")) == Order::GREATER);
  assert(String("abb").compareWith(String("aab")) == Order::GREATER);
  assert(String("abcde").compareWith(String("abcdd")) == Order::GREATER);
  assert(String("fdsafsdafa1").compareWith(String("fdsafsdafa1")) == Order::EQUAL);
  assert(String("a1111fdsafs").compareWith(String("a1111fdsafs")) == Order::EQUAL);
  assert(String("afdaf23121").compareWith(String("afdaf23121")) == Order::EQUAL);

  assert(String("32121") > String("111111111111"));
  assert(String("32121") >= String("111111111111"));
  assert(String("3212111111111") > String("111111"));
  assert(String("3212111111111") >= String("111111"));
  assert(String("1212111111111") < String("131111"));
  assert(String("3212111111111") != String("111111"));
  assert(String("3212111111111") == String("3212111111111"));

  string[2] = 'w';
  printf("Testing substring matching!\n");
  printf("Simple cases\n");
  assert(String("1").beIndexOf(String("1234")) == 0);
  assert(String("5").beIndexOf(String("1234")) == 4);
  printf("Middle cases\n");
  printf("Result is %u\n", String("ABCDABD").beIndexOf(String("BBCABCDABABCDABCDABDE")));
  assert(String("ABCDABD").beIndexOf(String("BBCABCDABABCDABCDABDE")) == 13);
  assert(String("ABCDABD").beIndexOf(String("BBCABCDABABCDABCDABEE")) ==  strlen("BBCABCDABABCDABCDABEE"));

  srand(time(NULL));
  for (int i = 0; i < 20; ++i) {
    auto length = rand() % 40 + 20;
    auto testStr = new char[length + 1];
    testStr[length] = '\0';
    for (int k = 0; k < length; ++k) {
      testStr[k] = (rand() % 26) + 'A';
    }
    String testString(testStr);
    assert(String("1").beIndexOf(testString) == testString.getLength());
  }
  // Test the get C-style string function.
  auto raw = string.cStr();
  printf("%s\n", raw);

  return 0;
}
