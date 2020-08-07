#include "Millis.h"

#ifdef _WIN32

#include <time.h>
unsigned long millis() { return static_cast<unsigned long>(clock()); }

#endif
