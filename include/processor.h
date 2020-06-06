#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
  long last_active_jiffies_{0}, last_jiffies_{0};
};

#endif