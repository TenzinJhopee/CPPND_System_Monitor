#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    static int previdle, previowait;
    static int prevuser, prevnice, prevsystem, previrq, prevsoftirq, prevsteal;
};

#endif