/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __repl_curses_h__
#define __repl_curses_h__

#include <string>

namespace curses {
void diffCurses(const std::string &left, const std::string &right);
}

#endif //__repl_curses_h__