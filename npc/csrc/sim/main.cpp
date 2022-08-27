#include <Vexample.h>

#include "verilated.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dut.h>

int main(int argc, char** argv, char** env) {
  Dut top(0);

  top.init_sim(1000000);
  top.reset(10);

  while(top.sim_continue()) {
    top.single_cycle();
  }
  top.close_sim();

  return 0;
}
