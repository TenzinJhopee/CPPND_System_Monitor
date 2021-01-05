#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memTotal, memFree;
  string line, total, free;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string temp;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream1(line);
    linestream1 >> temp >> total;
    std::getline(stream, line);
    std::istringstream linestream2(line);
    linestream2 >> temp >> free;
  }

  memTotal = stof(total);
  memFree = stof(free);

  return (memTotal - memFree) / memTotal;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long int ans;
  string uptime, line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }

  ans = static_cast<long int>(stof(uptime));
  return ans;
}
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> utilization;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    string temp;
    linestream >> temp;
    while (linestream >> temp) {
      utilization.push_back(temp);
    }
  }

  return utilization;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string line, key, value;
  int totalProcesses = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        totalProcesses = stoi(value);
        return totalProcesses;
      }
    }
  }
  return totalProcesses;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line, key, value;
  int runningProcesses = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "proces_running") {
        runningProcesses = stoi(value);
        return runningProcesses;
      }
    }
  }
  return runningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string line;
  std::string path = kProcDirectory + std::to_string(pid) + kCmdlineFilename;
  std::ifstream stream(path);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }

  return line;
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string line, key, value;
  std::string path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  std::ifstream stream(path);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        int ram = stoi(value) / 100;
        return std::to_string(ram);
      }
    }
  }
  return string();
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::string line, key, value;
  std::string path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  std::ifstream stream(path);
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return value;
      }
    }
  }
  return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string line, key, value;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream, line)) {
      int pos1, pos2, pos3;
      string uid, username;
      pos1 = line.find(":", 0);
      pos2 = line.find(":", pos1+1);
      pos3 = line.find(":", pos2+1);
      username = line.substr(0, pos1);
      uid = line.substr(pos2+1, pos3 - pos2 - 1);
      if (uid == LinuxParser::Uid(pid)) {
        return username;
      }
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string line, value;
  std::string path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  std::ifstream stream(path);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 22; ++i) {
        linestream >> value;
    }
    int time = stoi(value) / sysconf(_SC_CLK_TCK);
    return time;
  }
  return 0;
 }

float LinuxParser::CpuUtilization(int pid) { 
  std::string line, value;
  long utime, stime, cutime, cstime, startime;
  std::string path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  std::ifstream stream(path);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 1; i <= 22; ++i) {
      linestream >> value;
      if (i == 14) {
        utime = stoi(value);
      }
      if(i == 15) {
        stime = stoi(value);
      }
      if (i == 16) {
        cutime = stoi(value);
      }

      if(i == 17) {
        cstime = stoi(value);
      }
      if(i == 22) {
        startime = stoi(value);
      }
    }

    long total_time = utime + stime + cutime + cstime;
    long uptime = LinuxParser::UpTime();
    long seconds = uptime - startime / sysconf(_SC_CLK_TCK);
    float cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) * 1.0 / seconds;
    return cpu_usage;
  }
  return 0.0;
 }