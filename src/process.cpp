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

Process::Process(const int pid) : pid_(pid), cpu_(CpuUtilization()) {}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  long active_jiffies = LinuxParser::ActiveJiffies(pid_);
  float seconds = (float)Process::UpTime();

  if (seconds == 0) return 0;

  const float cpuUsage = ((active_jiffies / sysconf(_SC_CLK_TCK)) / seconds);

  return cpuUsage;
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
