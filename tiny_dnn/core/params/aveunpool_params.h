/*
    Copyright (c) 2013, Taiga Nomi and the respective contributors
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.
*/
#pragma once

#include <utility>
#include <vector>

#include "tiny_dnn/core/params/params.h"

namespace tiny_dnn {
namespace core {

struct average_unpooling_layer_worker_specific_storage {
  using io_connections = std::vector<std::pair<size_t, size_t>>;
  using wi_connections = std::vector<std::pair<size_t, size_t>>;
  using wo_connections = std::vector<std::pair<size_t, size_t>>;

  std::vector<io_connections> weight2io;  // weight_id -> [(in_id, out_id)]
  std::vector<wi_connections> out2wi;     // out_id -> [(weight_id, in_id)]
  std::vector<wo_connections> in2wo;      // in_id -> [(weight_id, out_id)]

  std::vector<std::vector<size_t>> bias2out;

  average_unpooling_layer_worker_specific_storage() {}

  average_unpooling_layer_worker_specific_storage(size_t weight2io_size,
                                                  size_t out2wi_size,
                                                  size_t in2wo_size,
                                                  size_t bias2out_size)
    : weight2io(weight2io_size),
      out2wi(out2wi_size),
      in2wo(in2wo_size),
      bias2out(bias2out_size) {}
};

class aveunpool_params : public Params {
 public:
  shape3d in;
  shape3d out;
  shape3d window;
  size_t stride;
  float_t scale_factor;
};

inline aveunpool_params &Params::aveunpool() {
  return *(static_cast<aveunpool_params *>(this));
}

}  // namespace core
}  // namespace tiny_dnn