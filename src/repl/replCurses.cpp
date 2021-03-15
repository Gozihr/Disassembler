/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "replCurses.h"
#include "interfaces/helpers.h"
#include "interfaces/pch.h"
#include <curses.h>

namespace curses {
void diffCurses(const std::string &left, const std::string &right) {
  initscr();

  printw("Diff window");
  WINDOW *mainWindow = initscr();
  int y = 0, x = 0;
  getmaxyx(mainWindow, y, x);
  WINDOW *subwindow1 = newwin(0, x / 2, 0, 0);
  WINDOW *subwindow2 = newwin(0, 0, 0, x / 2);

  refresh();

  box(subwindow1, 0, 0);
  StringHelpers::stringFunc trim = StringHelpers::trim;
  std::vector<std::string> strLines;
  StringHelpers::Split(left, strLines, '\n', trim);
  int yText = 1;
  for (auto line : strLines) {
    mvwprintw(subwindow1, yText, 1, line.c_str());
    yText += 1;
  }

  box(subwindow2, 0, 0);
  StringHelpers::Split(right, strLines, '\n', trim);
  yText = 1;
  for (auto line : strLines) {
    mvwprintw(subwindow2, yText, 1, line.c_str());
    yText += 1;
  }

  refresh();
  wrefresh(subwindow1);
  wrefresh(subwindow2);

  getch();
  delwin(subwindow1);
  delwin(subwindow2);

  endwin();
}
} // namespace curses