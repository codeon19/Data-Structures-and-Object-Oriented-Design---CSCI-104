#include "../lib/LoadWindow.h"

using namespace std;

LoadWindow::LoadWindow() : QWidget(NULL)
{

  debug = NULL; // to make sure no mem leaks 

  // LoadWindow
  mainLayout = new QVBoxLayout;

  instructions = new QLabel("Enter the file to debug below!");
  mainLayout->addWidget(instructions);
  
  fileName = new QLineEdit();
  mainLayout->addWidget(fileName);

  loadButtonLayout = new QHBoxLayout;

  mainLayout->addLayout(loadButtonLayout);

  quitButton = new QPushButton("Quit");
  loadButtonLayout->addWidget(quitButton);

  loadButton = new QPushButton("Load");
  loadButtonLayout->addWidget(loadButton);

  setLayout(mainLayout);

  // ErrorWin

  ErrorLayout = new QVBoxLayout;
  ErrorWin = new QWidget;
  error = new QLabel("Error Loading File");
  ErrorLayout->addWidget(error);
  closeButton = new QPushButton("Close");
  ErrorLayout->addWidget(closeButton);
  
  ErrorWin->setLayout(ErrorLayout);

  QObject::connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
  QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));

  // ErrorWin button 
  QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

}
LoadWindow::~LoadWindow(){

  delete debug;

  delete instructions;
  delete fileName;

  delete loadButton;
  delete quitButton;

  delete loadButtonLayout;
  delete mainLayout;

  delete error;
  delete closeButton;
  delete ErrorLayout;
  delete ErrorWin;

}

void LoadWindow::loadButtonClicked(){ 
  string file = fileName->text().toStdString(); // converting the QString fileName to a StdString
  
  ifstream inFile(file.c_str());

  if(!(inFile.good())){ // if the file was not opened correctly, then show the error window

    ErrorWin->show();
  }
  else{

    debug = new DebuggerWindow(file);
    debug->show();
    this->hide();

  }
}

// quit button 
void LoadWindow::quitButtonClicked(){ QApplication::quit();}

// close button
void LoadWindow::closeButtonClicked(){ ErrorWin->hide();}