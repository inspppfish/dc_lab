#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vshift_register.h"

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  Vshift_register *top = new Vshift_register();
  Verilated::traceEverOn(true);
  VerilatedVcdC *trace = new VerilatedVcdC;
  top->trace(trace, 99);
  trace->open("shift_register.vcd");

  bool pass = true;

  for (int i = 0; i < 8; ++i) {
    top->clk = 0;
    top->data_in = 0xAA;
    top->opt = i;

    top->eval();

    top->clk = 1;
    top->eval();

    trace->dump(2 * i);

    uint8_t expected_output;
    switch (i) {
    case 0:
      expected_output = 0x00;
      break;
    case 1:
      expected_output = 0xAA;
      break;
    case 2:
      expected_output = 0x55;
      break;
    case 3:
      expected_output = 0xAA;
      break;
    case 4:
      expected_output = 0xD5;
      break;
    case 5:
      expected_output = 0xAA;
      break;
    case 6:
      expected_output = 0x55;
      break;
    case 7:
      expected_output = 0xAA;
      break;
    }

    if (top->data_out != expected_output) {
      pass = false;
      std::cout << "Test " << i << " failed." << std::endl;
      printf("Got %x, expect %x\n", top->data_out, expected_output);
    } else {
      std::cout << "Test " << i << " passed." << std::endl;
    }
  }

  trace->close();
  delete top;
  delete trace;

  if (pass) {
    std::cout << "All tests passed." << std::endl;
    return 0;
  } else {
    std::cout << "Some tests failed." << std::endl;
    return 1;
  }
}
