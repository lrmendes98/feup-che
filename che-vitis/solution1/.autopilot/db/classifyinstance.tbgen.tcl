set moduleName classifyinstance
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {classifyinstance}
set C_modelType { int 8 }
set C_modelArgList {
	{ new_point_features int 64 regular {pointer 0}  }
	{ new_point_classification_id int 8 unused  }
	{ best_points int 64 regular {array 23 { 2 1 } 1 1 }  }
	{ num_classes int 32 unused  }
	{ known_points_soa int 64 regular {array 186990 { 1 1 } 1 1 }  }
	{ num_points int 32 regular  }
	{ num_features int 32 unused  }
}
set C_modelArgMapList {[ 
	{ "Name" : "new_point_features", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "new_point_features","cData": "long","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "new_point_classification_id", "interface" : "wire", "bitwidth" : 8, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "new_point_classification_id","cData": "char","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "best_points", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "best_points","cData": "long","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "num_classes", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "num_classes","cData": "int","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "known_points_soa", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "known_points_soa","cData": "long","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "num_points", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "num_points","cData": "int","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "num_features", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "num_features","cData": "int","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 8,"bitSlice":[{"low":0,"up":7,"cElement": [{"cName": "return","cData": "char","bit_use": { "low": 0,"up": 7},"cArray": [{"low" : 0,"up" : 1,"step" : 0}]}]}]} ]}
# RTL Port declarations: 
set portNum 26
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ new_point_features sc_in sc_lv 64 signal 0 } 
	{ new_point_classification_id sc_in sc_lv 8 signal 1 } 
	{ best_points_address0 sc_out sc_lv 5 signal 2 } 
	{ best_points_ce0 sc_out sc_logic 1 signal 2 } 
	{ best_points_we0 sc_out sc_lv 8 signal 2 } 
	{ best_points_d0 sc_out sc_lv 64 signal 2 } 
	{ best_points_q0 sc_in sc_lv 64 signal 2 } 
	{ best_points_address1 sc_out sc_lv 5 signal 2 } 
	{ best_points_ce1 sc_out sc_logic 1 signal 2 } 
	{ best_points_q1 sc_in sc_lv 64 signal 2 } 
	{ num_classes sc_in sc_lv 32 signal 3 } 
	{ known_points_soa_address0 sc_out sc_lv 18 signal 4 } 
	{ known_points_soa_ce0 sc_out sc_logic 1 signal 4 } 
	{ known_points_soa_q0 sc_in sc_lv 64 signal 4 } 
	{ known_points_soa_address1 sc_out sc_lv 18 signal 4 } 
	{ known_points_soa_ce1 sc_out sc_logic 1 signal 4 } 
	{ known_points_soa_q1 sc_in sc_lv 64 signal 4 } 
	{ num_points sc_in sc_lv 32 signal 5 } 
	{ num_features sc_in sc_lv 32 signal 6 } 
	{ ap_return sc_out sc_lv 8 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "new_point_features", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "new_point_features", "role": "default" }} , 
 	{ "name": "new_point_classification_id", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "new_point_classification_id", "role": "default" }} , 
 	{ "name": "best_points_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "best_points", "role": "address0" }} , 
 	{ "name": "best_points_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "best_points", "role": "ce0" }} , 
 	{ "name": "best_points_we0", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "best_points", "role": "we0" }} , 
 	{ "name": "best_points_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "best_points", "role": "d0" }} , 
 	{ "name": "best_points_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "best_points", "role": "q0" }} , 
 	{ "name": "best_points_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "best_points", "role": "address1" }} , 
 	{ "name": "best_points_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "best_points", "role": "ce1" }} , 
 	{ "name": "best_points_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "best_points", "role": "q1" }} , 
 	{ "name": "num_classes", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "num_classes", "role": "default" }} , 
 	{ "name": "known_points_soa_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":18, "type": "signal", "bundle":{"name": "known_points_soa", "role": "address0" }} , 
 	{ "name": "known_points_soa_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "known_points_soa", "role": "ce0" }} , 
 	{ "name": "known_points_soa_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "known_points_soa", "role": "q0" }} , 
 	{ "name": "known_points_soa_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":18, "type": "signal", "bundle":{"name": "known_points_soa", "role": "address1" }} , 
 	{ "name": "known_points_soa_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "known_points_soa", "role": "ce1" }} , 
 	{ "name": "known_points_soa_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "known_points_soa", "role": "q1" }} , 
 	{ "name": "num_points", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "num_points", "role": "default" }} , 
 	{ "name": "num_features", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "num_features", "role": "default" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8"],
		"CDFG" : "classifyinstance",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "new_point_features", "Type" : "None", "Direction" : "I"},
			{"Name" : "new_point_classification_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "best_points", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "num_classes", "Type" : "None", "Direction" : "I"},
			{"Name" : "known_points_soa", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "num_points", "Type" : "None", "Direction" : "I"},
			{"Name" : "num_features", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.histogram_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dadddsub_64ns_64ns_64_5_full_dsp_1_U1", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dadddsub_64ns_64ns_64_5_full_dsp_1_U2", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dadddsub_64ns_64ns_64_5_full_dsp_1_U3", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dadd_64ns_64ns_64_5_full_dsp_1_U4", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dmul_64ns_64ns_64_4_max_dsp_1_U5", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dmul_64ns_64ns_64_4_max_dsp_1_U6", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dcmp_64ns_64ns_1_2_no_dsp_1_U7", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	classifyinstance {
		new_point_features {Type I LastRead 2 FirstWrite -1}
		new_point_classification_id {Type I LastRead -1 FirstWrite -1}
		best_points {Type IO LastRead 216 FirstWrite 1}
		num_classes {Type I LastRead -1 FirstWrite -1}
		known_points_soa {Type I LastRead 25 FirstWrite -1}
		num_points {Type I LastRead 0 FirstWrite -1}
		num_features {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "1", "EnableSignal" : "ap_enable_pp1"}
	{"Pipeline" : "3", "EnableSignal" : "ap_enable_pp3"}
	{"Pipeline" : "4", "EnableSignal" : "ap_enable_pp4"}
]}

set Spec2ImplPortList { 
	new_point_features { ap_none {  { new_point_features in_data 0 64 } } }
	new_point_classification_id { ap_none {  { new_point_classification_id in_data 0 8 } } }
	best_points { ap_memory {  { best_points_address0 mem_address 1 5 }  { best_points_ce0 mem_ce 1 1 }  { best_points_we0 mem_we 1 8 }  { best_points_d0 mem_din 1 64 }  { best_points_q0 mem_dout 0 64 }  { best_points_address1 MemPortADDR2 1 5 }  { best_points_ce1 MemPortCE2 1 1 }  { best_points_q1 MemPortDOUT2 0 64 } } }
	num_classes { ap_none {  { num_classes in_data 0 32 } } }
	known_points_soa { ap_memory {  { known_points_soa_address0 mem_address 1 18 }  { known_points_soa_ce0 mem_ce 1 1 }  { known_points_soa_q0 mem_dout 0 64 }  { known_points_soa_address1 MemPortADDR2 1 18 }  { known_points_soa_ce1 MemPortCE2 1 1 }  { known_points_soa_q1 MemPortDOUT2 0 64 } } }
	num_points { ap_none {  { num_points in_data 0 32 } } }
	num_features { ap_none {  { num_features in_data 0 32 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
