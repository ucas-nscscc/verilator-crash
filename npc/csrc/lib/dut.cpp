#include <dut.h>
#include "verilated_vcd_c.h"

void Dut::init_sim(int time)
{
  simTime = time;
  init_wave();
}

bool Dut::sim_continue()
{
  bool ret = wave_continue();
  return ret;
}

void Dut::close_sim()
{
  close_wave();
}

void Dut::single_cycle() 
{
  dut.clk = 0; dut.eval();
  dump_wave();
  dut.clk = 1; dut.eval();
  dump_wave();
}

void Dut::reset(int n) 
{
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}

#ifdef OPEN_WAVE
void Dut::init_wave() 
{
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  dut.trace(tfp, 99);  // Trace 99 levels of hierarchy (or see below)
  tfp->open("./simx.vcd");
}

bool Dut::wave_continue()
{
  return dut.contextp()->time() < simTime;
}

void Dut::dump_wave()
{
  dut.contextp()->timeInc(1);
  tfp->dump(dut.contextp()->time());
}

void Dut::close_wave()
{
  tfp->close();
  delete tfp;
}
#endif
