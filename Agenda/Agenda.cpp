#include "AgendaUI.h"

AgendaUI aui;

Storage* Storage::instance_=NULL;

int main() {
  aui.OperationLoop();
  return 0;
}
