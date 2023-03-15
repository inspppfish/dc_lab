module adder4(
  input [3:0] a,
  input [3:0] b,
  input opt, // 0 add, 1 sub
  output carry,
  output zero,
  output overflow,
  output [3:0] y // result
);

  wire [3:0] mask;
  wire [3:0] real_b;
  assign mask = {4{opt}};
  assign real_b = b ^ mask;
  assign {carry, y} = real_b + a + {3'b000, opt};
  assign zero = ~(|y);
  assign overflow = (a[4-1] == real_b[4-1]) && (y[4-1] != a[4-1]);

endmodule
