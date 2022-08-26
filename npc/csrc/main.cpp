#include "Vexample.h"

#include "verilated.h"
#ifdef OPEN_WAVE
#include "verilated_vcd_c.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int simTime = 100;

int main(int argc, char** argv, char** env) {
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);
  Vexample* top = new Vexample{contextp};

#ifdef OPEN_WAVE
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace(tfp, 99);  // Trace 99 levels of hierarchy (or see below)
  tfp->open("./simx.vcd");
#endif

  while (contextp->time() < simTime && !contextp->gotFinish()) {
    contextp->timeInc(1);
    int a = rand() & 1;
    int b = rand() & 1;
    top->a = a;
    top->b = b;
    top->eval();

#ifdef OPEN_WAVE
    tfp->dump(contextp->time());
#endif

    printf("a = %d, b = %d, f = %d\n", a, b, top->f);
    assert(top->f == a ^ b);
    // sleep(1);
  }
  delete top;
  delete contextp;

#ifdef OPEN_WAVE
  tfp->close();
  delete tfp;
#endif

  return 0;
}
