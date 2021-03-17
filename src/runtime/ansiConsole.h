// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef __ansi_console_h__
#define __ansi_console_h__

namespace ansiColors {
void enableAnsiColors();
} // namespace ansiColors

#ifndef _WIN32
void ansiColors::enableAnsiColors() {}
#endif
#endif // __ansi_console_h__