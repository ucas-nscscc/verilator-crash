module mux (
  input clk,
  input rst,
  input a,
  input b,
  input s,
  output c
);
  assign c = s ? a : b;
endmodule
