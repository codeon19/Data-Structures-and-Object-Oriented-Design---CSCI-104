#include <QApplication>
#include <vector>
#include "lib/LoadWindow.h"

int main(int argc, char *argv[]) {
  
  QApplication app(argc, argv);

  LoadWindow m;

  m.setWindowTitle("Debugger");
  m.show();

  return app.exec();
}