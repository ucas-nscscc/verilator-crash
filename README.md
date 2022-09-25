# Verilator 使用示例

## 简介

这是基于"[一生一芯](https://ysyx.oscc.cc/)"计划项目框架修改得到的仿真环境, 目的是帮助快速上手 Verilator. 

通过运行
```bash
bash init.sh subproject-name
```
进行初始化.

## 快速上手

请先参考["一生一芯"预学习阶段讲义](https://ysyx.oscc.cc/docs/prestudy/prestudy.html)构建基本开发环境.

使用该框架需要先克隆南京大学的 nvboard 项目, 具体方法为

```bash
bash init.sh nvboard
```

此外, 若使用的 shell 不是 bash, 需要手动设置环境变量 `NVBOARD_HOME` 为 nvboard 项目的根目录.

若要运行该项目, 需在 shell 中进入 `npc/` 目录, 然后使用 `make`, 目前支持的参数如下:

+ `compile_hw`: 使用 verilator 编译 verilog 源码, 将其转换为 c++ 模型;

+ `compile_sim`: 使用 verilator 编译 verilog 源码与仿真源码, 生成运行仿真的可执行程序;

+ `run_sim`: 运行仿真的可执行程序, 并在 `npc/` 目录下生成波形文件 `simx.vcd`;

+ `run_nvboard`: 在虚拟 FPGA nvboard 上运行 verilog 设计. 运行效果如下(运行操作系统为 Ubuntu 20.04):

![nvboard-exec-example](./img/nvboard-exec-example.png)

现象为 LED 灯由右至左依次亮起, 并不断循环.

## TODO

目前项目尚不支持用户便捷配置(如是否开启波形等), 后续考虑进一步完善.
