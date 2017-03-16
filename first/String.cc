
#include <cstring>
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
String::String(char *str) : length(strlen(str)), storage(new char[length]) {
  std::copy(str, str + length, storage);
}

/**
 * The copy constructor
 * @param string
 */
String::String(const String &string) : length(string.length), storage(new char[length]) {
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
}

/**
 *
 * @param n
 * @return
 */
char &String::operator[](std::size_t n) {
  logger->log("non-const subscript accessor");
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
  storage = new char[length];
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
 * @return
 */
const char *String::cStr() const {
  return storage;
}

/**
 *
 * @return
 */
char *String::cStr() {
  return storage;
}

/**
 * Implements the KMP algorithm.
 * @param subString
 * @return
 */
std::size_t String::posSub(const String &subString) const {

  return 0;
}
std::size_t String::getLength() {
  return length;
}

Order String::compareWith(const String &anotherString) const& {
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
bool String::operator!=(const String &anotherString) const& {
  return compareWith(anotherString) != Order::EQUAL;
}
bool String::operator==(const String &anotherString) const& {
  return compareWith(anotherString) == Order::EQUAL;
}
bool String::operator>=(const String &anotherString) const& {
  return compareWith(anotherString) != Order::SMALLER;
}
bool String::operator<=(const String &anotherString) const& {
  return compareWith(anotherString) != Order::GREATER;
}
bool String::operator>(const String &anotherString) const& {
  return compareWith(anotherString) == Order::GREATER;
}
bool String::operator<(const String &anotherString) const& {
  return compareWith(anotherString) == Order::SMALLER;
}

}

Logger *Logger::logger_ = nullptr;