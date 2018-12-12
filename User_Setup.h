#pragma once

#define DEBUG 1

#ifdef DEBUG
#define DEGUG_INIT Serial.begin(115200)
#define PRINT_FUNCTION Serial.println(__FUNCTION__)
#define PRINT_DEBUG_MSG(m) Serial.print("DEBUG:");Serial.println(m)
#else
#define PRINT_FUNCTION 1
#define PRINT_DEBUG_MSG 1
#endif

