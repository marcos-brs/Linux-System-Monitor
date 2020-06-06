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

int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
  long active_jiffies = LinuxParser::ActiveJiffies(pid_);
  float seconds = (float)Process::UpTime();

  if (seconds == 0) return 0;

  const float cpuUsage = ((active_jiffies / sysconf(_SC_CLK_TCK)) / seconds);

  return cpuUsage;
}

string Process::Command() { return LinuxParser::Command(pid_); }

string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return LinuxParser::User(pid_); }

long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

bool Process::operator<(Process const& a) const { return cpu_ < a.cpu_; }

bool Process::operator>(Process const& a) const { return cpu_ > a.cpu_; }
