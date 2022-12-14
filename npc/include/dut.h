#ifndef _DUT_H
#define _DUT_H

#include <generated/vheader.h>

class Dut {
private:
  TOP_NAME dut;
  VerilatedVcdC* tfp;
  int simTime;
public:
  Dut(int simTime): simTime(simTime) {};
  Dut(void) {};
  void init_sim(int time);
  bool sim_continue();
  void close_sim();

  void single_cycle();
  void reset(int n);

  TOP_NAME* getDut() { return &dut; }
#ifdef OPEN_WAVE
  void init_wave();
  bool wave_continue();
  void dump_wave();
  void close_wave();
#else
  void init_wave() {}
  bool wave_continue() { return true; }
  void dump_wave() {}
  void close_wave() {}
#endif
};

#endif
