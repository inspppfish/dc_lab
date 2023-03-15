#include "Valu4.h"
#include "nvboard.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#define TOP Valu4

VerilatedContext *contextp = NULL;
VerilatedVcdC *tfp = NULL;

static TOP *top;

void sim_init() {
  contextp = new VerilatedContext;
  top = new TOP;
}

void sim_end() {
  delete contextp;
  delete top;
}

int main() {
  sim_init();
  int n = 100000;
  while (n--) {
    top->eval();
  }

  for (int i = -8; i <= 7; i++) {
    for (int j = -8; j <= 7; j++) {
      sim_init();
      top->opt = 0b110;
      top->a = i;
      top->b = j;
      int n = 100000;
      while (n--) {
        top->eval();
      }
      int result;
      if (i < j) {
        result = 1;
      } else {
        result = 0;
      }
      if (top->y != result) {
        printf("a: %d, b: %d, should be %d, got %d\n", i, j, result, top->y);
      } else {
        printf("a: %d, b: %d, got %d, OK!\n", i, j, result);
      }
      sim_end();
    }
  }
}
