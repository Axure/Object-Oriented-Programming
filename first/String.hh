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

  /**
   * Log the message.
   *
   * Will be empty under release mode.
   * @param message
   */
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

  /**
   * The empty formatted log function under release mode.
   * @tparam TParams
   * @param format
   * @param args
   */
  template<class ...TParams>
  void logf(const char *format, TParams &&...args) {
  }

#endif
 private:
  static std::shared_ptr<Logger> logger_;
 public:

  /**
   * The singleton pattern.
   * Get the logger anywhere.
   * @return
   */
  static std::shared_ptr<Logger> getLogger() {
    if (logger_ == nullptr) { logger_ = std::make_shared<Logger>(); }
    return logger_;
  }
};

namespace Axurez {

/**
 * An `enum class` representing the states of comparison.
 */
enum class Order {
  GREATER, EQUAL, SMALLER
};

/**
 * The class for strings.
 */
class String {
  /**
   * Private data members.
   */
 private:
  /**
   * The length of the string. Cached to avoid calling `strlen` too often.
   */
  std::size_t length;
  /**
   * The actual storage.
   * Implemented as a raw pointer with heap-allocated memory.
   */
  char *storage = nullptr;
  /**
   * The logger.
   * Currently not injected, but directly coupled.
   */
  std::shared_ptr<Logger> logger = Logger::getLogger();

  /**
   * The preprocessed data for the KMP algorithm.
   * Mutable since it's only sort of cache.
   */
  mutable std::size_t *longestPrefixSuffix = nullptr;

  /**
   * Indicating whether the string has been modified since last match.
   */
  bool modified = false;
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
  String(const char (&str)[n])  : length(n - 1), storage(new char[n]()) {
    std::copy(str, str + length, storage);
    logger->log("const template lvalue constructor");
  }

  /**
   *
   * @tparam n The length of the char array.
   * @param str
   */
  template<std::size_t n>
  String(const char (&&str)[n])  : length(n - 1), storage(new char[n]()) {
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
   * @param parentString
   * @return The position of the first matched sub string. `-1` if not any.
   */
  std::size_t beIndexOf(const String &parentString) const;

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
  /**
   * The private methods for internal manipulations.
   */
 private:
  void calculateLongestPrefixSuffix() const;
};
}
