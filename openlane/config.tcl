set ::env(FP_DEF_TEMPLATE) $::env(CARAVEL_UPRJ_ROOT)/openlane/user_project_wrapper/fixed_dont_change/user_project_wrapper.def
set ::env(MAGIC_ZEROIZE_ORIGIN) 0
set ::env(FP_SIZING) absolute
set ::env(DIE_AREA) "0 0 2980.2 2980.2"
set ::env(CORE_AREA) "12 12 2968.2 2968.2"
set ::env(RUN_CVC) 0
set ::env(PIN_UNIT) 2.4
set ::env(FP_IO_VEXTEND) [expr {2 * $::env(PIN_UNIT)}]
set ::env(FP_IO_HEXTEND) [expr {2 * $::env(PIN_UNIT)}]
set ::env(FP_IO_VLENGTH) $::env(PIN_UNIT)
set ::env(FP_IO_HLENGTH) $::env(PIN_UNIT)
set ::env(FP_IO_VTHICKNESS_MULT) 4
set ::env(FP_IO_HTHICKNESS_MULT) 4
set ::env(FP_PDN_CORE_RING) 1
set ::env(FP_PDN_CORE_RING_VWIDTH) 3.1
set ::env(FP_PDN_CORE_RING_HWIDTH) 3.1
set ::env(FP_PDN_CORE_RING_VOFFSET) 14
set ::env(FP_PDN_CORE_RING_HOFFSET) 16
set ::env(FP_PDN_CORE_RING_VSPACING) 1.7
set ::env(FP_PDN_CORE_RING_HSPACING) 1.7
set ::env(FP_PDN_HOFFSET) 3
set ::env(FP_PDN_HPITCH_MULT) 1
set ::env(FP_PDN_HPITCH) [expr {60 + $::env(FP_PDN_HPITCH_MULT) * 30}]
set ::env(FP_PDN_VWIDTH) 3.1
set ::env(FP_PDN_HWIDTH) 3.1
set ::env(DESIGN_IS_CORE) 1
set ::env(SYNTH_STRATEGY) "AREA 0"
set ::env(SYNTH_FIXED_NETLIST) "/home/egor/proj/fpga2/impl/open/designs/user_project_wrapper.v"
set ::env(CLOCK_PERIOD) 100
set ::env(CLOCK_PORT) "wb_clk_i"
set ::env(CLOCK_NET) "wb_clk_i"
set ::env(CLOCK_NETS_EVAL) "{get_full_name \[get_nets -of_objects ariel_fpga_top_inst.config_block_clk_buf.tech_clkbuf/Z\]} {get_full_name \[get_nets -of_objects ariel_fpga_top_inst.config_vrnode_clk_buf.tech_clkbuf/Z\]} {get_full_name \[get_nets -of_objects ariel_fpga_top_inst.config_hrnode_clk_buf.tech_clkbuf/Z\]} "
set ::env(PL_MAX_DISPLACEMENT_X) 3000
set ::env(PL_MAX_DISPLACEMENT_Y) 1000
set ::env(FP_PDN_AUTO_ADJUST) 0
set ::env(FP_PDN_IRDROP) 0
set ::env(FP_PDN_HORIZONTAL_HALO) 1
set ::env(FP_PDN_VERTICAL_HALO) 1
set ::env(FP_PDN_VPITCH) 110
set ::env(FP_PDN_VSPACING) 10
set ::env(FP_PDN_HSPACING) 41.9
set ::env(PL_TIME_DRIVEN) 1
set ::env(PL_TARGET_DENSITY) 0.48
set ::env(PL_RESIZER_ALLOW_SETUP_VIOS) 1
set ::env(GRT_ALLOW_CONGESTION) 1
set ::env(GRT_ADJUSTMENT) 0.0
set ::env(FP_PDN_CFG) "/home/egor/proj/fpga2/impl/open/pdn_cfg.tcl"
set ::env(FP_TAP_HORIZONTAL_HALO) 5
set ::env(RUN_KLAYOUT_XOR) 0
set ::env(STA_WRITE_LIB) 0
set ::env(RUN_IRDROP_REPORT) 0
set ::env(PRIMARY_SIGNOFF_TOOL) klayout
set ::env(VERILOG_FILES_BLACKBOX) "/home/egor/proj/fpga2/impl/open/macros.v"
set ::env(EXTRA_LEFS) "/home/egor/proj/fpga2/impl/open/best/fpga_struct_block/results/final/lef/fpga_struct_block.lef /home/egor/proj/fpga2/impl/open/best/efuse_ctrl/results/final/lef/efuse_ctrl.lef"
set ::env(EXTRA_LIBS) "/home/egor/proj/fpga2/impl/open/best/fpga_struct_block/results/final/lib/fpga_struct_block.lib /home/egor/proj/fpga2/impl/open/best/efuse_ctrl/results/final/lib/efuse_ctrl.lib"
set ::env(EXTRA_GDS_FILES) "/home/egor/proj/fpga2/impl/open/best/fpga_struct_block/results/final/gds/fpga_struct_block.gds /home/egor/proj/fpga2/impl/open/best/efuse_ctrl/results/final/gds/efuse_ctrl.gds"
set ::env(MACRO_PLACEMENT_CFG) "designs/user_project_wrapper/macro.cfg"
set ::env(DESIGN_NAME) user_project_wrapper
set ::env(VERILOG_FILES) "designs/user_project_wrapper/ariel_fpga_top_fromvhdl.v designs/user_project_wrapper/fpga_tech.v designs/user_project_wrapper/user_project_wrapper.v"
set ::env(BASE_SDC_FILE) "designs/user_project_wrapper/user_project_wrapper.sdc"
set ::env(FP_PIN_ORDER_CFG) "designs/user_project_wrapper/pin.cfg"
set ::env(SYNTH_DRIVING_CELL) "gf180mcu_fd_sc_mcu7t5v0__buf_1"
set ::env(SYNTH_DRIVING_CELL_PIN) "Z"
set ::env(ROUTING_CORES) 24

