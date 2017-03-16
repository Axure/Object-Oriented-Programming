
#include <cstring>
#include <cassert>
#include "String.hh"
namespace Axurez {

enum ORDER {
  SMALLER = 0, EQUAL = 1, GREATER = 2
};

/**
 *
 * @tparam T
 * @param thiz
 * @param that
 * @return An integer. If this is bigger than that, return 2. If they are equal, return 1, else 0.
 */
template<class T>
inline ORDER compareSingle(const T &thiz, const T &that) {
  Logger::getLogger()->logf("%d， %d, %d\n", static_cast<ORDER>((static_cast<int >(thiz > that) << 1)
      + static_cast<int >(thiz == that)), thiz, that);
  return static_cast<ORDER>((static_cast<int >(thiz > that) << 1)
      + static_cast<int >(thiz == that));
}

template<>
inline ORDER compareSingle<char>(const char &thiz, const char &that) {
  Logger::getLogger()->logf("%d， %c, %c\n", (static_cast<int>(thiz > that) << 1)
      + static_cast<int>(thiz == that), thiz, that);
  return static_cast<ORDER>((static_cast<int >(thiz > that) << 1)
      + static_cast<int >(thiz == that));
}

/**
 * The default constructor.
 */
String::String() : length(0), storage(new char[1]()) {

}

/**
 * The constructor from C-style strings.
 * @param str
 */
String::String(char *str) : length(strlen(str)), storage(new char[length]()) {
  std::copy(str, str + length, storage);
}

/**
 * The copy constructor
 * @param string
 */
String::String(const String &string) : length(string.length), storage(new char[length]()) {
  std::copy(string.storage, string.storage + length, storage);
}

/**
 * The copy constructor
 * @param string
 */
String::String(String &&string) : length(string.length), storage(string.storage) {
  string.storage = nullptr;
}

/**
 *
 */
String::~String() {
  logger->log("destroyed!");
  if (storage != nullptr) {
    delete[] storage;
  }
  if (longestPrefixSuffix != nullptr) {
    delete[] longestPrefixSuffix;
  }
}

/**
 *
 * @param n
 * @return
 */
char &String::operator[](std::size_t n) {
  logger->log("non-const subscript accessor");
  logger->log("content could be modified");
  modified = true;
  return storage[n];
}

/**
 *
 * @param n
 * @return
 */
const char &String::operator[](std::size_t n) const {
  logger->log("const subscript accessor");
  return storage[n];
}

/**
 *
 * @param string
 * @return
 */
String &String::operator=(const String &string) {
  length = string.length;
  storage = new char[length]();
  std::copy(storage, storage + length, string.storage);
  return *this;
}

/**
 *
 * @param string
 * @return
 */
String &String::operator=(String &&string) {
  length = string.length;
  storage = string.storage;
  string.storage = nullptr;
  return *this;
}

/**
 *
 * @return The const raw C-style string (char pointer).
 */
const char *String::cStr() const {
  return storage;
}

/**
 * Get the raw C-style string inside the string class.
 * This method is not const, thus you can modify directly the content inside the class.
 * @return
 */
char *String::cStr() {
  logger->log("cStr access in a non-const way");
  logger->log("content could be modified");
  modified = true;
  return storage;
}

/**
 * TODO: Implements the KMP algorithm.
 * @param parentString
 * @return `length + 1` if not found.
 * // TODO: search iterator abstraction.
 * // TODO: facade and different impls.
 */
std::size_t String::beIndexOf(const String &parentString) const {
  if (longestPrefixSuffix == nullptr || modified == true) {
    calculateLongestPrefixSuffix();
  }
  std::size_t i = 0, j = 0;
  while (i < parentString.length) {
    while (parentString[i] != storage[j]) {
      i += 1;
      if (i >= parentString.length) return parentString.length;
    };
    while (parentString[i] == storage[j]) {
      i += 1; j += 1;
      if (j == length) return i - j;
    };
    if (j != length) {
      j = longestPrefixSuffix[j - 1];
    } else {
      logger->logf("result: %d\n", i - j);
      return i - j;
    }
    logger->logf("search: %u, %u, %u\n", i, j, length);
  }
  logger->logf("result: %d\n", parentString.length);
  return parentString.length;
//  for (std::size_t i = 0; i < parentString.length; ++i) {
//    if (storage[j] == parentString[i]) {
//      j += 1;
//    } else {
//      j = longestPrefixSuffix[j];
//      i =
//    }
////    while (j != 0 && storage[j] != parentString[i]) {
////      assert(j > 0);
////      assert(j > longestPrefixSuffix[j]);
////      j = longestPrefixSuffix[j];
////    }
////    if (storage[j] == parentString[i]) {
////      j += 1;
////    }
//    logger->logf("search: %u, %u, %u\n", i, j, length);
//    if (j == length) {
//      assert(i - j + 1 >= 0);
//      return i - j + 1;
//    }
//  }
//  return parentString.length;
}

/**
 * Getter of the length of the string.
 * @return
 */
std::size_t String::getLength() {
  return length;
}

/**
 * The implementation of the string comparison function.
 * @param anotherString
 * @return
 */
Order String::compareWith(const String &anotherString) const &{
  logger->log("lvalue comparator");
  auto thisLonger = compareSingle(this->length, anotherString.length);
  switch (thisLonger) {
    case GREATER:
      for (int i = 0; i < anotherString.length; ++i) {
        switch (compareSingle(this->operator[](i), anotherString[i])) {
          case GREATER:
            logger->log("Bigger");
            return Order::GREATER;
          case SMALLER:
            logger->log("Smaller");
            return Order::SMALLER;
          case EQUAL:
            logger->log("Equal");
            break;
        }
      }
      return Order::GREATER;
    case EQUAL:
    case SMALLER:
      for (int i = 0; i < this->length; ++i) {
        switch (compareSingle(this->operator[](i), anotherString[i])) {
          case GREATER:
            logger->log("Bigger");
            return Order::GREATER;
          case SMALLER:
            logger->log("Smaller");
            return Order::SMALLER;
          case EQUAL:
            logger->log("Equal");
            break;
        }
      }
    default:
      break;
  }
  switch (thisLonger) {
    case SMALLER:
      return Order::SMALLER;
    default:
      return Order::EQUAL;
  }
}

bool String::operator!=(const String &anotherString) const &{
  return compareWith(anotherString) != Order::EQUAL;
}

bool String::operator==(const String &anotherString) const &{
  return compareWith(anotherString) == Order::EQUAL;
}

bool String::operator>=(const String &anotherString) const &{
  return compareWith(anotherString) != Order::SMALLER;
}

bool String::operator<=(const String &anotherString) const &{
  return compareWith(anotherString) != Order::GREATER;
}

bool String::operator>(const String &anotherString) const &{
  return compareWith(anotherString) == Order::GREATER;
}

bool String::operator<(const String &anotherString) const &{
  return compareWith(anotherString) == Order::SMALLER;
}

void String::calculateLongestPrefixSuffix() const {
  if (longestPrefixSuffix != nullptr) {
    delete[] longestPrefixSuffix;
  }
  longestPrefixSuffix = new std::size_t[length]();
  std::size_t j = 0;
  longestPrefixSuffix[0] = 0;
  for (std::size_t i = 1; i < length; ++i) {
    while (j != 0 && storage[j] != storage[i]) {
      logger->logf("i: %u, j: %u\n", i, j);
      assert(j >= 0);
      assert(j > longestPrefixSuffix[j]);
      j = longestPrefixSuffix[j];
    }
    if (storage[j] == storage[i]) {
      j += 1;
    }
    assert(j < length);
    longestPrefixSuffix[i] = j;
  }
  logger->logf("lpf: ");
  for (int k = 0; k < length; ++k) {
    logger->logf("%u, ", longestPrefixSuffix[k]);
  }
  logger->logf("\n");
}

}

std::shared_ptr<Logger> Logger::logger_ = nullptr;