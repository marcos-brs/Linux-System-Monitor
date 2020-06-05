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
  long active_jiffies = LinuxParser::ActiveJiffies(pid_);
  long system_jiffies = LinuxParser::Jiffies();

  long active_duration = active_jiffies - last_active_jiffies_;
  long duration = system_jiffies - last_system_jiffies_;

  cpu_ = static_cast<float>(active_duration) / duration;

  last_active_jiffies_ = active_jiffies;
  last_system_jiffies_ = system_jiffies;

  return cpu_;
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
bool Process::operator<(Process const& a) const { return cpu_ < a.cpu_; }
bool Process::operator>(Process const& a) const { return cpu_ > a.cpu_; }
