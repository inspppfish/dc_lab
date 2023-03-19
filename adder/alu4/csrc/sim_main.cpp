#include "Valu4.h"
#include <iostream>
#include <verilated.h>

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Valu4 *top = new Valu4;

  for (int a = -8; a <= 7; ++a) {
    for (int b = -8; b <= 7; ++b) {
      top->a = a;
      top->b = b;
      top->opt = 6;
      top->eval();
      int expected_output = (a < b) ? 1 : 0;
      if (top->y != expected_output) {
        std::cerr << "Error: a = " << a << ", b = " << b
                  << ", opt = 110, output should be " << expected_output
                  << ", but get result " << top->y << std::endl;
      } else {
        std::cout << "ok!" << std::endl;
      }
    }
  }

  top->final();
  delete top;
  return 0;
}
