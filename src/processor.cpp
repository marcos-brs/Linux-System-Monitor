#include "processor.h"

#include <unistd.h>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  float delta_total, delta_active;

  long total_jiffies_start = LinuxParser::Jiffies();
  long active_jiffies_start = LinuxParser::ActiveJiffies();

  usleep(100000);

  long total_jiffies_end = LinuxParser::Jiffies();
  long active_jiffies_end = LinuxParser::ActiveJiffies();

  delta_total = total_jiffies_end - total_jiffies_start;
  delta_active = active_jiffies_end - active_jiffies_start;

  return delta_active / delta_total;
}