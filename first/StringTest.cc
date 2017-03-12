
#include <cstdio>
#include "String.hh"

using Axurez::String;

int main() {

  String string("hahaa");
  string[2] = 'w';

  // Test the get C-style string function.
  auto raw = string.cStr();
  printf("%s\n", raw);

  return 0;
}
