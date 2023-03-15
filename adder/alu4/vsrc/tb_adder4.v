/* verilator lint_off UNOPTFLAT */
module tb_adder4 (

);

  reg [3:0] inputa;
  reg [3:0] inputb;
  wire inputopt;
  reg c, z, of;
  reg [3:0] outputy;

  adder4 i0 (
    .a            (inputa),
    .b            (inputb),
    .opt          (inputopt),
    .carry        (c),
    .zero         (z),
    .overflow     (of),
    .y            (outputy)
  );

  initial begin 
    inputa = 1;
    inputb = 2;
    $display("a: %d, b: %d, y: %d", inputa, inputb, outputy);
  end

 endmodule
