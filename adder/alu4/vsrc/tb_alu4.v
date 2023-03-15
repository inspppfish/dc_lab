module tb_alu4(

);

  reg [3:0]inputa;
  reg [3:0]inputb;
  reg [2:0]inputopt;
  wire [3:0]outputs;
  reg [3:0]answer;
  
  alu4 i0 (
    .a        (inputa),
    .b        (inputb),
    .opt      (inputopt),
    .y        (outputs)
  );
  
  initial begin
    reg signed [4:0] i;
    reg signed [4:0] j;
    $display("start test");
    for (i=-8; i<=7; i=i+1)
      for (j=-8; j<=7; j=j+1) begin
        /* verilator lint_off WIDTH */
        inputa = i;
        inputb = j;
        inputopt = 3'b110;
        /* verilator lint_off STMTDLY */
        if (i < j)
          answer = 4'b0001;
        else 
          answer = 4'b0000;
        if (outputs != answer) begin
          $display("Error: a=%h, b=%h, output should be %h, but get result %h",
                    inputa, inputb, answer, outputs);
        end
        else 
          $display("ok!");
      end
    end

endmodule
