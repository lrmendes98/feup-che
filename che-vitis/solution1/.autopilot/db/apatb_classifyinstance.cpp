#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_new_point_features "../tv/cdatafile/c.classifyinstance.autotvin_new_point_features.dat"
#define AUTOTB_TVOUT_new_point_features "../tv/cdatafile/c.classifyinstance.autotvout_new_point_features.dat"
// wrapc file define:
#define AUTOTB_TVIN_new_point_classification_id "../tv/cdatafile/c.classifyinstance.autotvin_new_point_classification_id.dat"
#define AUTOTB_TVOUT_new_point_classification_id "../tv/cdatafile/c.classifyinstance.autotvout_new_point_classification_id.dat"
// wrapc file define:
#define AUTOTB_TVIN_k "../tv/cdatafile/c.classifyinstance.autotvin_k.dat"
#define AUTOTB_TVOUT_k "../tv/cdatafile/c.classifyinstance.autotvout_k.dat"
// wrapc file define:
#define AUTOTB_TVIN_best_points "../tv/cdatafile/c.classifyinstance.autotvin_best_points.dat"
#define AUTOTB_TVOUT_best_points "../tv/cdatafile/c.classifyinstance.autotvout_best_points.dat"
// wrapc file define:
#define AUTOTB_TVIN_num_classes "../tv/cdatafile/c.classifyinstance.autotvin_num_classes.dat"
#define AUTOTB_TVOUT_num_classes "../tv/cdatafile/c.classifyinstance.autotvout_num_classes.dat"
// wrapc file define:
#define AUTOTB_TVIN_known_points_soa "../tv/cdatafile/c.classifyinstance.autotvin_known_points_soa.dat"
#define AUTOTB_TVOUT_known_points_soa "../tv/cdatafile/c.classifyinstance.autotvout_known_points_soa.dat"
// wrapc file define:
#define AUTOTB_TVIN_num_points "../tv/cdatafile/c.classifyinstance.autotvin_num_points.dat"
#define AUTOTB_TVOUT_num_points "../tv/cdatafile/c.classifyinstance.autotvout_num_points.dat"
// wrapc file define:
#define AUTOTB_TVIN_num_features "../tv/cdatafile/c.classifyinstance.autotvin_num_features.dat"
#define AUTOTB_TVOUT_num_features "../tv/cdatafile/c.classifyinstance.autotvout_num_features.dat"
// wrapc file define:
#define AUTOTB_TVOUT_return "../tv/cdatafile/c.classifyinstance.autotvout_ap_return.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_new_point_features "../tv/rtldatafile/rtl.classifyinstance.autotvout_new_point_features.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_new_point_classification_id "../tv/rtldatafile/rtl.classifyinstance.autotvout_new_point_classification_id.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k "../tv/rtldatafile/rtl.classifyinstance.autotvout_k.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_best_points "../tv/rtldatafile/rtl.classifyinstance.autotvout_best_points.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_num_classes "../tv/rtldatafile/rtl.classifyinstance.autotvout_num_classes.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_known_points_soa "../tv/rtldatafile/rtl.classifyinstance.autotvout_known_points_soa.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_num_points "../tv/rtldatafile/rtl.classifyinstance.autotvout_num_points.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_num_features "../tv/rtldatafile/rtl.classifyinstance.autotvout_num_features.dat"
#define AUTOTB_TVOUT_PC_return "../tv/rtldatafile/rtl.classifyinstance.autotvout_ap_return.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  new_point_features_depth = 0;
  new_point_classification_id_depth = 0;
  k_depth = 0;
  best_points_depth = 0;
  num_classes_depth = 0;
  known_points_soa_depth = 0;
  num_points_depth = 0;
  num_features_depth = 0;
  return_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{new_point_features " << new_point_features_depth << "}\n";
  total_list << "{new_point_classification_id " << new_point_classification_id_depth << "}\n";
  total_list << "{k " << k_depth << "}\n";
  total_list << "{best_points " << best_points_depth << "}\n";
  total_list << "{num_classes " << num_classes_depth << "}\n";
  total_list << "{known_points_soa " << known_points_soa_depth << "}\n";
  total_list << "{num_points " << num_points_depth << "}\n";
  total_list << "{num_features " << num_features_depth << "}\n";
  total_list << "{ap_return " << return_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int new_point_features_depth;
    int new_point_classification_id_depth;
    int k_depth;
    int best_points_depth;
    int num_classes_depth;
    int known_points_soa_depth;
    int num_points_depth;
    int num_features_depth;
    int return_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
extern "C" char classifyinstance_hw_stub_wrapper(volatile void *, char, int, volatile void *, int, volatile void *, int, int);

extern "C" char apatb_classifyinstance_hw(volatile void * __xlx_apatb_param_new_point_features, char __xlx_apatb_param_new_point_classification_id, int __xlx_apatb_param_k, volatile void * __xlx_apatb_param_best_points, int __xlx_apatb_param_num_classes, volatile void * __xlx_apatb_param_known_points_soa, int __xlx_apatb_param_num_points, int __xlx_apatb_param_num_features) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
    char AESL_return;
    {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_return);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<8> > return_pc_buffer(1);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "return");
  
            // push token into output port buffer
            if (AESL_token != "") {
              return_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {
            ((char*)&AESL_return)[0] = return_pc_buffer[0].to_int64();
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_best_points);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<64> > best_points_pc_buffer(23);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "best_points");
  
            // push token into output port buffer
            if (AESL_token != "") {
              best_points_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {{
            int i = 0;
            for (int j = 0, e = 23; j < e; j += 1, ++i) {
            ((long long*)__xlx_apatb_param_best_points)[j] = best_points_pc_buffer[i].to_int64();
          }}}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return  AESL_return;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//new_point_features
aesl_fh.touch(AUTOTB_TVIN_new_point_features);
aesl_fh.touch(AUTOTB_TVOUT_new_point_features);
//new_point_classification_id
aesl_fh.touch(AUTOTB_TVIN_new_point_classification_id);
aesl_fh.touch(AUTOTB_TVOUT_new_point_classification_id);
//k
aesl_fh.touch(AUTOTB_TVIN_k);
aesl_fh.touch(AUTOTB_TVOUT_k);
//best_points
aesl_fh.touch(AUTOTB_TVIN_best_points);
aesl_fh.touch(AUTOTB_TVOUT_best_points);
//num_classes
aesl_fh.touch(AUTOTB_TVIN_num_classes);
aesl_fh.touch(AUTOTB_TVOUT_num_classes);
//known_points_soa
aesl_fh.touch(AUTOTB_TVIN_known_points_soa);
aesl_fh.touch(AUTOTB_TVOUT_known_points_soa);
//num_points
aesl_fh.touch(AUTOTB_TVIN_num_points);
aesl_fh.touch(AUTOTB_TVOUT_num_points);
//num_features
aesl_fh.touch(AUTOTB_TVIN_num_features);
aesl_fh.touch(AUTOTB_TVOUT_num_features);
CodeState = DUMP_INPUTS;
// print new_point_features Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_new_point_features, __xlx_sprintf_buffer.data());
  {
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_new_point_features);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_new_point_features, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.new_point_features_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_new_point_features, __xlx_sprintf_buffer.data());
}
// print new_point_classification_id Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_new_point_classification_id, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_new_point_classification_id);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_new_point_classification_id, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.new_point_classification_id_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_new_point_classification_id, __xlx_sprintf_buffer.data());
}
// print k Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_k);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_k, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.k_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k, __xlx_sprintf_buffer.data());
}
unsigned __xlx_offset_byte_param_best_points = 0;
// print best_points Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_best_points, __xlx_sprintf_buffer.data());
  {  __xlx_offset_byte_param_best_points = 0*8;
  if (__xlx_apatb_param_best_points) {
    for (int j = 0  - 0, e = 23 - 0; j != e; ++j) {
sc_bv<64> __xlx_tmp_lv = ((long long*)__xlx_apatb_param_best_points)[j];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_best_points, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(23, &tcl_file.best_points_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_best_points, __xlx_sprintf_buffer.data());
}
// print num_classes Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_num_classes, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_num_classes);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_num_classes, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.num_classes_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_num_classes, __xlx_sprintf_buffer.data());
}
unsigned __xlx_offset_byte_param_known_points_soa = 0;
// print known_points_soa Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_known_points_soa, __xlx_sprintf_buffer.data());
  {  __xlx_offset_byte_param_known_points_soa = 0*8;
  if (__xlx_apatb_param_known_points_soa) {
    for (int j = 0  - 0, e = 186990 - 0; j != e; ++j) {
sc_bv<64> __xlx_tmp_lv = ((long long*)__xlx_apatb_param_known_points_soa)[j];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_known_points_soa, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(186990, &tcl_file.known_points_soa_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_known_points_soa, __xlx_sprintf_buffer.data());
}
// print num_points Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_num_points, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_num_points);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_num_points, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.num_points_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_num_points, __xlx_sprintf_buffer.data());
}
// print num_features Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_num_features, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_num_features);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_num_features, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.num_features_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_num_features, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
char ap_return = classifyinstance_hw_stub_wrapper(__xlx_apatb_param_new_point_features, __xlx_apatb_param_new_point_classification_id, __xlx_apatb_param_k, __xlx_apatb_param_best_points, __xlx_apatb_param_num_classes, __xlx_apatb_param_known_points_soa, __xlx_apatb_param_num_points, __xlx_apatb_param_num_features);
CodeState = DUMP_OUTPUTS;
// print best_points Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_best_points, __xlx_sprintf_buffer.data());
  {  __xlx_offset_byte_param_best_points = 0*8;
  if (__xlx_apatb_param_best_points) {
    for (int j = 0  - 0, e = 23 - 0; j != e; ++j) {
sc_bv<64> __xlx_tmp_lv = ((long long*)__xlx_apatb_param_best_points)[j];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_best_points, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(23, &tcl_file.best_points_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_best_points, __xlx_sprintf_buffer.data());
}
// print return Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
  sc_bv<8> __xlx_tmp_lv = ((char*)&ap_return)[0];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data()); 
  
  tcl_file.set_num(1, &tcl_file.return_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
return ap_return;
}
