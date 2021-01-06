#include "processor.h"
#include <string>
#include <vector>

#include "linux_parser.h"


int Processor::previdle = 0;
int Processor::previowait = 0;
int Processor::prevuser = 0;
int Processor::prevnice = 0;
int Processor::prevsystem = 0;
int Processor::previrq = 0;
int Processor::prevsoftirq = 0;
int Processor::prevsteal = 0;



// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpu = LinuxParser::CpuUtilization();
    std::vector<int> values;
    for (auto& s : cpu) {
        int value = stoi(s);
        values.push_back(value);
    }

    int user, nice, system, idle, iowait, irq, softirq, steal;
    user = values[0];
    system = values[2];
    nice = values[1];
    idle = values[3];
    iowait = values[4];
    irq = values[5];
    softirq = values[6];
    steal = values[7];

    int PrevIdle = previdle + previowait;
    int Idle = idle + iowait;

    int PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    int NonIdle = user + nice + system + irq + softirq + steal;

    int PrevTotal = PrevIdle + PrevNonIdle;
    int Total = Idle + NonIdle;


    int totald = Total - PrevTotal;
    int idled = Idle + PrevIdle;

    float cpu_percentage = (totald - idled) * 1.0 / totald;

    previdle = idle;
    previowait = iowait;
    prevuser = user;
    prevnice = system;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;

    return cpu_percentage;

}