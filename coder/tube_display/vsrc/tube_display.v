module coder83 (
	input [7:0] x,
	output reg [2:0] y,
	output reg seg
);
	integer i;
	always @(x) begin
		y = 0;
		seg = 0;
		for (i = 0; i < 8; i = i+1)
			if (x[i] == 1) begin
				y = i[2:0];
				seg = 1;
			end
	end

endmodule

module decoder3tube (
	input [2:0] x,
	input en,
	output reg [6:0] y
);
	always @(x or en) begin
		if (en) begin
			case (x)
				3'b000 : y = 7'b0000001;
				3'b001 : y = 7'b1001111;
				3'b010 : y = 7'b0010010;
				3'b011 : y = 7'b0000110;
				3'b100 : y = 7'b1001100;
				3'b101 : y = 7'b0100100;
				3'b110 : y = 7'b0100000;
				3'b111 : y = 7'b0001111;
				default : y = 7'b0000000;
			endcase
		end
		else y = 7'b1111111;
	end;

endmodule

module tube_display(
	input [7:0] x,
	output [6:0] tube,	
	output [2:0] code3
);
	integer i;
	wire en;
	coder83 i0 (
		.x(x), 
		.y(code3),
		.seg(en)
	);
	decoder3tube i1 (
		.x(code3), 
		.y(tube),
		.en(en)
	);
endmodule


