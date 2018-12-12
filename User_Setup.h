#pragma once

#define DEBUG 1

#ifdef DEBUG
#define PRINT_DEBUG_MSG Serial.println(__FUNCTION__)
#else
#define PRINT_DEBUG_MSG 1
#endif

