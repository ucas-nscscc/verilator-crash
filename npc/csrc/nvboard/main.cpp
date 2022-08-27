#include <nvboard.h>
#include <dut.h>
#include <Vexample.h>

void nvboard_bind_all_pins(TOP_NAME* top);

int main() {
  Dut top;

  nvboard_bind_all_pins(top.getDut());
  nvboard_init();

  top.reset(10);

  while(1) {
    nvboard_update();
    top.single_cycle();
  }
}
