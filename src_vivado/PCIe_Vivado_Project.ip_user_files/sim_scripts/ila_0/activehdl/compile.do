vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xil_defaultlib
vlib activehdl/xpm

vmap xilinx_vip activehdl/xilinx_vip
vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm

vlog -work xilinx_vip  -sv2k12 "+incdir+/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/include" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../PCIe_Vivado_Project.srcs/sources_1/ip/ila_0/hdl/verilog" "+incdir+/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/include" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/home/chenxun/Software/Vivado/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../PCIe_Vivado_Project.srcs/sources_1/ip/ila_0/hdl/verilog" "+incdir+/home/chenxun/Software/Vivado/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../PCIe_Vivado_Project.srcs/sources_1/ip/ila_0/sim/ila_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

