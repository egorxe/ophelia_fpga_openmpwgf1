# Ophelia eFPGA GFMPW1 rerun

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) 

## General description

Ophelia is a test project implementing open-source Uranus eFPGA fabric for Open MPW GF1 using open source GF180 PDK and OpenLane flow. FPGA contains 112 4-input LUTs and uses Wishbone bus from Caravel test harness for bitstream loading. Project also contains 9 kBit eFuse array for nonvolatile FPGA config storage compiled with [this compiler](https://github.com/egorxe/gf180_efuse_compiler).

## Project implementation

Project is implemented for GlobalFoundries 180nm ASIC technology using OpenLane open source flow. Synthesis is done in two steps: first Yosys+GHDL are used for VHDL to Verilog translation, and then resulting Verilog source is synthesized by Yosys inside OpenLane flow. 

## FPGA flow

Uranus FPGA uses opensource flow for FPGA bitstream generation. Yosys (with optional GHDL frontend for VHDL) is used for synthesis and VPR for place and route. Flow glue and bitstream generation is done by custom Python scripts.

## Sources

This repository contains mainly implementation products (GDS/netlists/etc) needed for OpenMPW and test Caravel programs. VHDL sources of Uranus FPGA fabric, FPGA flow, tests and simulation scripts are stored in [gf180 branch of main Uranus repository](https://github.com/egorxe/uranus_fpga/tree/gf180). eFuse compiler resides in it's own [repository](https://github.com/egorxe/gf180_efuse_compiler).

## Documentation

Documentation is avaliable in [main Uranus repository](https://github.com/egorxe/uranus_fpga/blob/main/docs/index.rst).

## Changes since GFMPW0

* Fixed eFuse cells power connection issues which made eFuse testing impossible.
* Fixed hold timing issues in FPGA fabric config loading register chains which broke most of FPGA firmwares.
* Several small RTL improvements for automatic FPGA config loading from eFuse, OEB pins control, etc (see Uranus repository).
* Several improvements in eFuse Pcell such as increase in ammount of vias in critical nets, better signal buffering, more power capacitors, etc.
* Much better test coverage, thanks to introduction of SDF annotation capable cell models in GF180MCU PDK and full device level LVS in precheck.
