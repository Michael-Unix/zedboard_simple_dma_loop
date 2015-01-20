# zedboard\_simple\_dma\_loop

Simple AXI DMA loop back project on ZedBoard

## How to use

1. Generate Bitstream

  You should have latest Xilinx's [Vivado Design Suite](http://www.xilinx.com/products/design-tools/vivado.html) installed. Open `zedboard_simple_dma_loop.xpr` as other Vivado project. Run synthesis, implementation then generate bitstream. Once you got the `.bit` file, open hardware manager and program your ZedBoard.
  
2. Build the bare metal program

  In Vivado, use `File > Export > Export Hardware...` to get your `.hdf` file, or just keep the one in the repo (under folder `zedboard_simple_dma_loop.sdk`). Use `File > Launch SDK` to open the Xilinx SDK. SDK will create "Hardware Platform Specification" project automatically for you. Then create an Application Project with default settings and "Empty Application" template. Copy the `main.c` file in `zedboard_simple_dma_loop.sdk/simple_dma_loop/src` to your project. Build the project to get `.elf` runnable file.
