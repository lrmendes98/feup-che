############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project che-vitis
set_top classifyinstance
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/knn.c
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/knn.h
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/params.h
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/types.h
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/utils.c
add_files ../feup-che/Project/Project/OriginalProjectFiles-v0.6/utils.h
add_files -tb ../feup-che/Project/Project/OriginalProjectFiles-v0.6/main.c
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 20 -name default
#source "./che-vitis/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
