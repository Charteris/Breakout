#ifndef LOGS_H
#define LOGS_H

#include <iostream>

#define ASCII_BOLD "\u001b[1m"
#define ASCII_RESET "\u001b[0m"
#define ASCII_GREEN "\u001b[32m"
#define ASCII_RED "\u001b[31m"
#define ASCII_YELLOW "\u001b[33m"
#define ASCII_BLUE "\u001b[36m"

#define INFO(str)                                                                          \
  std::cout << "[" << ASCII_BOLD << ASCII_GREEN << "INFO" << ASCII_RESET << "]  | " << str \
            << std::endl;
#define ERROR(str)                                                                        \
  std::cout << "[" << ASCII_BOLD << ASCII_RED << "ERROR" << ASCII_RESET << "]  | " << str \
            << std::endl;
#define WARN(str)                                                                           \
  std::cout << "[" << ASCII_BOLD << ASCII_YELLOW << "WARN" << ASCII_RESET << "]  | " << str \
            << std::endl;

#ifdef PRINT_DEBUG_LOGS
#define DEBUG(str)                                                                         \
  std::cout << "[" << ASCII_BOLD << ASCII_BLUE << "DEBUG" << ASCII_RESET << "]  | " << str \
            << std::endl;
#else
#define DEBUG(str)
#endif

namespace logs {

/**
 * Redirects the stdout and stderr logs to output files on instantiation
 */
inline void openLogs() {
  std::freopen("bin/log.txt", "w", stdout);
  std::freopen("bin/error-log.txt", "w", stderr);
  DEBUG("Redirected stdout and stderr");
}

/**
 * Closes logs once the config is destroyed
 */
inline void closeLogs() {
  DEBUG("Closing stdout and stderr");
  std::fclose(stdout);
  std::fclose(stderr);
}

}  // namespace logs

#endif