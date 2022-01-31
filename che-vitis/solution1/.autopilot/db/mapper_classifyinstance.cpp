#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" char classifyinstance(volatile void *, char, int, long long*, int, long long*, int, int);
extern "C" char apatb_classifyinstance_hw(volatile void * __xlx_apatb_param_new_point_features, char __xlx_apatb_param_new_point_classification_id, int __xlx_apatb_param_k, volatile void * __xlx_apatb_param_best_points, int __xlx_apatb_param_num_classes, volatile void * __xlx_apatb_param_known_points_soa, int __xlx_apatb_param_num_points, int __xlx_apatb_param_num_features) {
  // Collect __xlx_best_points__tmp_vec
  vector<sc_bv<64> >__xlx_best_points__tmp_vec;
  for (int j = 0, e = 23; j != e; ++j) {
    __xlx_best_points__tmp_vec.push_back(((long long*)__xlx_apatb_param_best_points)[j]);
  }
  int __xlx_size_param_best_points = 23;
  int __xlx_offset_param_best_points = 0;
  int __xlx_offset_byte_param_best_points = 0*8;
  long long* __xlx_best_points__input_buffer= new long long[__xlx_best_points__tmp_vec.size()];
  for (int i = 0; i < __xlx_best_points__tmp_vec.size(); ++i) {
    __xlx_best_points__input_buffer[i] = __xlx_best_points__tmp_vec[i].range(63, 0).to_uint64();
  }
  // Collect __xlx_known_points_soa__tmp_vec
  vector<sc_bv<64> >__xlx_known_points_soa__tmp_vec;
  for (int j = 0, e = 186990; j != e; ++j) {
    __xlx_known_points_soa__tmp_vec.push_back(((long long*)__xlx_apatb_param_known_points_soa)[j]);
  }
  int __xlx_size_param_known_points_soa = 186990;
  int __xlx_offset_param_known_points_soa = 0;
  int __xlx_offset_byte_param_known_points_soa = 0*8;
  long long* __xlx_known_points_soa__input_buffer= new long long[__xlx_known_points_soa__tmp_vec.size()];
  for (int i = 0; i < __xlx_known_points_soa__tmp_vec.size(); ++i) {
    __xlx_known_points_soa__input_buffer[i] = __xlx_known_points_soa__tmp_vec[i].range(63, 0).to_uint64();
  }
  // DUT call
  char ap_return = classifyinstance(__xlx_apatb_param_new_point_features, __xlx_apatb_param_new_point_classification_id, __xlx_apatb_param_k, __xlx_best_points__input_buffer, __xlx_apatb_param_num_classes, __xlx_known_points_soa__input_buffer, __xlx_apatb_param_num_points, __xlx_apatb_param_num_features);
// print __xlx_apatb_param_best_points
  sc_bv<64>*__xlx_best_points_output_buffer = new sc_bv<64>[__xlx_size_param_best_points];
  for (int i = 0; i < __xlx_size_param_best_points; ++i) {
    __xlx_best_points_output_buffer[i] = __xlx_best_points__input_buffer[i+__xlx_offset_param_best_points];
  }
  for (int i = 0; i < __xlx_size_param_best_points; ++i) {
    ((long long*)__xlx_apatb_param_best_points)[i] = __xlx_best_points_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_known_points_soa
  sc_bv<64>*__xlx_known_points_soa_output_buffer = new sc_bv<64>[__xlx_size_param_known_points_soa];
  for (int i = 0; i < __xlx_size_param_known_points_soa; ++i) {
    __xlx_known_points_soa_output_buffer[i] = __xlx_known_points_soa__input_buffer[i+__xlx_offset_param_known_points_soa];
  }
  for (int i = 0; i < __xlx_size_param_known_points_soa; ++i) {
    ((long long*)__xlx_apatb_param_known_points_soa)[i] = __xlx_known_points_soa_output_buffer[i].to_uint64();
  }
return ap_return;
}
