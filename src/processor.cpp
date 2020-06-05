#include "processor.h"

#include <unistd.h>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long active_jiffies = LinuxParser::ActiveJiffies();
  long idle_jiffies = LinuxParser::IdleJiffies();

  long active_duration = active_jiffies - last_active_jiffies_;
  long idle_duration = idle_jiffies - last_idle_jiffies_;

  float utilization =
      static_cast<float>(active_duration) / (active_duration + idle_duration);

  last_active_jiffies_ = active_duration;
  last_idle_jiffies_ = idle_duration;

  return utilization;
}