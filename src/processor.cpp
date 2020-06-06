#include "processor.h"

#include <unistd.h>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  const float non_idle = LinuxParser::ActiveJiffies();
  const float total = LinuxParser::Jiffies();

  // If there is no previous information, compute the long-term value for
  // utilization and update previous information.
  if (last_active_jiffies_ == 0 && last_jiffies_ == 0) {
    last_active_jiffies_ = non_idle;
    last_jiffies_ = total;
    return non_idle / total;
  }

  const float total_delta = total - last_jiffies_;
  const float non_idle_delta = non_idle - last_active_jiffies_;

  return non_idle_delta / total_delta;
}