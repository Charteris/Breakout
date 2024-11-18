#ifndef LOGS_H
#define LOGS_H

#include <iostream>

#define INFO(str) std::cout << " [INFO] | " << str << std::endl;
#define ERROR(str) std::cout << "[ERROR] | " << str << std::endl;

#ifdef PRINT_DEBUG_LOGS
#define DEBUG(str) std::cout << "[DEBUG] | " << str << std::endl;
#else
#define DEBUG(str)
#endif

#endif