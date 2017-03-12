
#include <cstring>
#include "String.hh"
namespace Axurez {


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
  if (storage != nullptr) {
    delete storage;
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
String &String::operator=(String && string) {
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

}

Logger *Logger::logger_ = nullptr;