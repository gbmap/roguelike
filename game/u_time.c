
#include "u_time.h"
#include <sys/time.h>

uint8_t DELTA_TIME = 0;
uint16_t STEP_MS = 200;

uint64_t time_ms() {
  struct timeval tv;

  gettimeofday(&tv, 0);
  return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}
