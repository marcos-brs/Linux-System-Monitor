#include "processor.h"

#include <unistd.h>

#include "linux_parser.h"

float Processor::Utilization() {
  const long active_jiffies = LinuxParser::ActiveJiffies();
  const long jiffies = LinuxParser::Jiffies();

  // If there is no previous information, compute the long-term value for
  // utilization and update previous information.
  if (last_active_jiffies_ == 0 && last_jiffies_ == 0) {
    last_active_jiffies_ = active_jiffies;
    last_jiffies_ = jiffies;
    return active_jiffies / jiffies;
  }

  const float active_jiffies_delta = active_jiffies - last_active_jiffies_;
  const float jiffies_delta = jiffies - last_jiffies_;

  last_active_jiffies_ = active_jiffies;
  last_jiffies_ = jiffies;

  if (jiffies_delta == 0) return 0.0;

  return active_jiffies_delta / jiffies_delta;
}