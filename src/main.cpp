#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  int n = system.Processes().size() <= 10 ? system.Processes().size() : 10;
  NCursesDisplay::Display(system, n);
}