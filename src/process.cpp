#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) { pid_ = pid; };

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  long jiffies_start, jiffies_end;
  long uptime_start, uptime_end;
  float delta_jiffies, delta_time;

  jiffies_start = LinuxParser::ActiveJiffies(pid_);
  uptime_start = LinuxParser::UpTime(pid_);

  usleep(100000);

  jiffies_end = LinuxParser::ActiveJiffies(pid_);
  uptime_end = LinuxParser::UpTime(pid_);

  delta_jiffies = jiffies_end - jiffies_start;
  delta_time = uptime_end - uptime_start;

  return delta_jiffies / delta_time;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  long ram = std::stol(LinuxParser::Ram(pid_));
  long ram_a = std::stol(LinuxParser::Ram(a.pid_));

  return ram < ram_a;
}