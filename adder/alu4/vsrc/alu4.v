module alu4 (
  input [3:0]a,
  input [3:0]b,
  input [2:0]opt,
  output [3:0]y
); 

  wire zero;
  wire overflow;
  wire [3:0] result;
  /* verilator lint_off UNOPTFLAT */
  reg [3:0] yout;
  assign y = yout;
  adder4 i0 (
    .a      (a),
    .b      (b),
    .opt    (1'b1),
    .zero   (zero),
    .carry  (),
    .overflow (overflow),
    .y      (result)
  );

always @(*) begin
  case(opt)
    3'b000 : yout = a+b;
    3'b001 : yout = a-b;
    3'b010 : yout = ~a;
    3'b011 : yout = a&b;
    3'b100 : yout = a|b;
    3'b101 : yout = a^b;
    3'b110 : yout = {3'b000, result[4-1] ^ overflow};
    3'b111 : yout = {3'b000, zero};
  endcase
end

endmodule

