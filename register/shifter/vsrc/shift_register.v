module shift_register(
  input clk,
  input [7:0] data_in,
  input [2:0] opt,
  output [7:0] data_out
);

reg [7:0] reg_data;

always @(posedge clk) begin
  case (opt) 
    3'b000 : reg_data <= 8'b0;
    3'b001 : reg_data <= data_in;
    3'b010 : reg_data <= {1'b0, reg_data[7:1]};
    3'b011 : reg_data <= {reg_data[6:0], 1'b0};
    3'b100 : reg_data <= {reg_data[7], reg_data[7:1]};
    3'b101 : reg_data <= {reg_data[6:0], data_in[0]};
    3'b110 : reg_data <= {reg_data[0], reg_data[7:1]};
    3'b111 : reg_data <= {reg_data[6:0], reg_data[7]};
  endcase 
end

assign data_out = reg_data;

endmodule

