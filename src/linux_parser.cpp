#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iomanip>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, kernel, hlp;
  string line;
  std::ifstream filestream(kProcDirectory + kVersionFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> os >> hlp >> kernel;
  }
  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line, key;
  float mem_total = 0, mem_free = 0, mem_info = 0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> mem_info) {
        if (key == "MemTotal:") {
          mem_total = mem_info;
        } else if (key == "MemFree:") {
          mem_free = mem_info;
        }

        if (mem_total != 0 && mem_free != 0) break;
      }
    }
  }
  return (mem_total - mem_free) / mem_total;
}

long LinuxParser::UpTime() {
  string line;
  long value;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value;
}

long LinuxParser::Jiffies() {
  return LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies();
}

long LinuxParser::ActiveJiffies(int pid) {
  string line, trash;
  long utime = 0, stime = 0, cutime = 0, cstime = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 13; i++) linestream >> trash;

    linestream >> utime >> stime >> cutime >> cstime;
  }
  return utime + stime + cutime + cstime;
}

long LinuxParser::ActiveJiffies() {
  std::vector<string> cpu = LinuxParser::CpuUtilization();
  long user = std::stol(cpu[CPUStates::kUser_]),
       nice = std::stol(cpu[CPUStates::kNice_]),
       system = std::stol(cpu[CPUStates::kSystem_]),
       irq = std::stol(cpu[CPUStates::kIRQ_]),
       softirq = std::stol(cpu[CPUStates::kSoftIRQ_]),
       steal = std::stol(cpu[CPUStates::kSteal_]);
  // guest = std::stol(cpu[CPUStates::kGuest_]),
  // guestnice = std::stol(cpu[CPUStates::kGuestNice_]);

  return user + nice + system + irq + softirq + steal /* + guest + guestnice*/;
}

long LinuxParser::IdleJiffies() {
  std::vector<string> cpu = LinuxParser::CpuUtilization();
  long idle = std::stol(cpu[CPUStates::kIdle_]),
       iowait = std::stol(cpu[CPUStates::kIOwait_]);

  return idle + iowait;
}

vector<string> LinuxParser::CpuUtilization() {
  std::vector<string> cpu_utilization;
  string line;
  string info;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> info) {
        if (info == "cpu") {
          while (linestream >> info) cpu_utilization.push_back(info);
          return cpu_utilization;
        }
      }
    }
  }
  return cpu_utilization;
}

int LinuxParser::TotalProcesses() {
  string line, key;
  int total_process = 0, value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          total_process = value;
          break;
        }
      }
    }
  }
  return total_process;
}

int LinuxParser::RunningProcesses() {
  string line, key;
  int run_proc = 0, value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          run_proc = value;
          break;
        }
      }
    }
  }
  return run_proc;
}

string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);

    if (line != "") {
      return line;
    }
  }
  return "None";
}

string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::stringstream ram;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        ram << std::fixed << std::setprecision(3) << stof(value) / 1000;
        return ram.str();
      }
    }
  }
  return "0";
}

string LinuxParser::Uid(int pid) {
  string line, key, value;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return value;
      }
    }
  }
  return "0";
}

string LinuxParser::User(int pid) {
  string line;
  string username, password, uid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> password >> uid;
      if (uid == LinuxParser::Uid(pid)) {
        return username;
      }
    }
  }
  return string();
}

long LinuxParser::UpTime(int pid) {
  string line, trash;
  long start_time;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 21; i++) linestream >> trash;
    linestream >> start_time;
    return LinuxParser::UpTime() - start_time / sysconf(_SC_CLK_TCK);
  }
  return 0;
}