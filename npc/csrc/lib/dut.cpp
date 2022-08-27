#include <Vexample.h>
#include <dut.h>
#ifdef OPEN_WAVE
#include "verilated_vcd_c.h"
#endif

void Dut::init_sim(int time)
{
  simTime = time;
#ifdef OPEN_WAVE
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  dut.trace(tfp, 99);  // Trace 99 levels of hierarchy (or see below)
  tfp->open("./simx.vcd");
#endif
}

bool Dut::sim_continue()
{
  bool ret = 
#ifdef OPEN_WAVE
  dut.contextp()->time() < simTime &&
#endif
  true;
  return ret;
}

void Dut::close_sim()
{
#ifdef OPEN_WAVE
  tfp->close();
  delete tfp;
#endif
}

void Dut::single_cycle() {
  dut.clk = 0; dut.eval();
#ifdef OPEN_WAVE
    dut.contextp()->timeInc(1);
    tfp->dump(dut.contextp()->time());
#endif
  dut.clk = 1; dut.eval();
#ifdef OPEN_WAVE
    dut.contextp()->timeInc(1);
    tfp->dump(dut.contextp()->time());
#endif
}

void Dut::reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}
