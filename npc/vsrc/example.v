module example(
  input clk,
  input rst,
  output reg [15:0] led
);

  reg [31:0] count;
  always@(posedge clk) begin
    if (rst) begin
      count <= 32'd0;
    end else begin
      count <= (count == 5000000) ? 32'd0 : count + 1;
    end
  end

  always@(posedge clk) begin
    if (rst) begin
      led <= 16'd1;
    end else if(count == 0) begin
      led <= {led[14:0], led[15]};
    end
  end

endmodule
