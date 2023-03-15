#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vadder8.h"
#include "nvboard.h"

#define TOP Vadder8

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static TOP* top;

void nvboard_bind_all_pins(TOP* top);

void sim_init(){
  contextp = new VerilatedContext;
  top = new TOP;
}

void sim_exit() {

}

int main() {
  sim_init();
  nvboard_bind_all_pins(top);
  nvboard_init();
  while (true) {
	top->eval();
	nvboard_update();
  }
  sim_exit();
}

