#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vm_mux42.h"
#include "nvboard.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vm_mux42* top;

void nvboard_bind_all_pins(Vm_mux42 * top);

void step_and_dump_wave(){
  top->eval();
  contextp->timeInc(1);
  tfp->dump(contextp->time());
  nvboard_update();
}
void sim_init(){
  contextp = new VerilatedContext;
  tfp = new VerilatedVcdC;
  top = new Vm_mux42;
  contextp->traceEverOn(true);
  top->trace(tfp, 0);
  tfp->open("dump.vcd");
}

void sim_exit(){
  step_and_dump_wave();
  tfp->close();
}


int main() {
  sim_init();
  nvboard_bind_all_pins(top);
  nvboard_init();
  while (true) {
	top->a=0b11111111;  step_and_dump_wave();
					top->a=0b00010001;  step_and_dump_wave();
	top->a=0b00011011;  step_and_dump_wave();
					top->a=0b00010001;  step_and_dump_wave();
	top->a=0b11110000;  step_and_dump_wave();
					top->a=0b00010001;  step_and_dump_wave();
	top->a=0b00000001;  step_and_dump_wave();
					top->a=0b00010001;  step_and_dump_wave();
  }
  sim_exit();
}

