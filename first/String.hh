#include <cstddef>
#include <algorithm>
#include <memory>

#include <iostream>

/**
 * A simple logger class.
 */
class Logger {
 public:
  Logger() {}

  ~Logger() {

  }

  void log(const char *message) {
#ifdef DEBUG___
    std::cout << message << std::endl;
#else
#endif
  }

#ifdef DEBUG___

  template<class ...TParams>
  void logf(const char* format, TParams&& ...args) {
      printf(format, std::forward<TParams>(args)...);
  }
#else
  template<class ...TParams>
  void logf(const char* format, TParams&& ...args) {
  }
#endif
 private:
  static Logger *logger_;
 public:

  static Logger *getLogger() {
    if (logger_ == nullptr) logger_ = new Logger();
    return logger_;
  }
};


namespace Axurez {

enum class Order {
  GREATER, EQUAL, SMALLER
};

/**
 * The class for strings.
 */
class String {
 private:
  std::size_t length;
  char *storage = nullptr;
  Logger *logger = Logger::getLogger();
 public:
  /**
   * The default constructor.
   */
  String();

  /**
   * The constructor from C-style strings.
   * @param str
   */
  String(char *str);

  /**
   *
   * @tparam n The length of the char array.
   * @param str
   */
  template<std::size_t n>
  String(const char (&str)[n])  : length(n), storage(new char[n]) {
    std::copy(str, str + length, storage);
    logger->log("const template lvalue constructor");
  }

  /**
   *
   * @tparam n The length of the char array.
   * @param str
   */
  template<std::size_t n>
  String(const char (&&str)[n])  : length(n), storage(new char[n]) {
    std::copy(str, str + length, storage);
    logger->log("const template rvalue constructor");
  }

  /**
   * The copy constructor
   * @param string
   */
  String(const String &string);

  /**
 * The copy constructor
 * @param string
 */
  String(String &&string);

  /**
   * The lvalue const reference assignment operator.
   * @return
   */
  String &operator=(const String &);

  /**
   * The rvalue reference assignment operator.
   * @return
   */
  String &operator=(String &&);

  /**
   * The destructor.
   */
  ~String();

  /**
   * The methods
   */
 public:
  /**
   *
   * @param n
   * @return
   */
  const char &operator[](std::size_t n) const;
  /**
   *
   * @param n
   * @return
   */
  char &operator[](std::size_t n);
  /**
   *
   * @return
   */
  const char *cStr() const;
  /**
   *
   * @return The raw C-string behind the class. Mutable.
   */
  char *cStr();

  /**
   * Matches a given sub string in the current string.
   * @param subString
   * @return The position of the first matched sub string. `-1` if not any.
   */
  std::size_t posSub(const String &subString) const;

  /**
   * Get the length of the string.
   * @return The length of the string.
   */
  std::size_t getLength();

  Order compareWith(const String &anotherString) const &;
  bool operator<(const String &anotherString) const &;
  bool operator>(const String &anotherString) const &;
  bool operator<=(const String &anotherString) const &;
  bool operator>=(const String &anotherString) const &;
  bool operator==(const String &anotherString) const &;
  bool operator!=(const String &anotherString) const &;
};
}
