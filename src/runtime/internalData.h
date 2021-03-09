/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __internal_data_h__
#define __internal_data_h__

#include <memory>

#include <LIEF/ELF/Binary.hpp>
#include <LIEF/MachO/Binary.hpp>
#include <LIEF/PE/Binary.hpp>

union BinaryInternal {
  std::unique_ptr<LIEF::ELF::Binary> elfBinary;
  std::unique_ptr<LIEF::PE::Binary> peBinary;
  std::unique_ptr<LIEF::MachO::Binary> machOBinary;
};



#endif //__internal_data_h__