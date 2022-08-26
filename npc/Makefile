VFLAGS=-Wall -Iobj_dir -DOPEN_WAVE=1

all:
	@echo "Write this Makefile by your self."

compile_hw:
	@echo "Compiling RTL code"
	verilator ${VFLAGS} --cc --trace ./vsrc/example.v
	@echo "Done."

compile_sim: compile_hw
# $(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Compiling simulation code..."
	verilator ${VFLAGS} --cc --exe --build --trace ./csrc/main.cpp ./vsrc/example.v
	@echo "Done."

run_sim: compile_sim
	@obj_dir/Vexample

clean:
	rm -rf obj_dir *.vcd

include ../Makefile
