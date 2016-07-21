#include "../lib/DebuggerWindow.h"

#include <iostream>
#include <QBrush>

using namespace std;

DebuggerWindow::DebuggerWindow(string file) : QWidget(NULL){

  inspect = NULL; // so no mem leaks

  backend = new Facile(file); // the backend with the Facile objec

  vector<string> text = backend->getText(); // the display text

  scroll = new QListWidget(); // where the text will be displayed 

  for(int i = 0; i < text.size(); i++){
    scroll->addItem(QString::fromStdString(text[i])); // adding in the text
  }

  // setting initial pointer
  QBrush background(Qt::green);
  currentItem = scroll->item(0);
  currentItem->setBackground(background);

  debugLayout = new QVBoxLayout;

  debugLayout->addWidget(scroll);

  controllerLayout = new QHBoxLayout;

  breakPointButton = new QPushButton("Break");
  controllerLayout->addWidget(breakPointButton);

  continueButton = new QPushButton("Continue");
  controllerLayout->addWidget(continueButton);

  stepButton = new QPushButton("Step");
  controllerLayout->addWidget(stepButton);

  nextButton = new QPushButton("Next");
  controllerLayout->addWidget(nextButton);

  inspectButton = new QPushButton("Inspect");
  controllerLayout->addWidget(inspectButton);

  resetButton = new QPushButton("Reset");
  controllerLayout->addWidget(resetButton);

  debugLayout->addLayout(controllerLayout);

  quitDButton = new QPushButton("Quit");
  debugLayout->addWidget(quitDButton);

  setLayout(debugLayout);

  // ErrorWin

  ErrorLayout = new QVBoxLayout;
  ErrorWin = new QWidget;
  error = new QLabel("");
  ErrorLayout->addWidget(error);
  closeButton = new QPushButton("Close");
  ErrorLayout->addWidget(closeButton);
  
  ErrorWin->setLayout(ErrorLayout);

  // ErrorWin Buttons
  QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

  // debugLayout Buttons
  QObject::connect(scroll, SIGNAL(currentRowChanged(int)), this, SLOT(preBreak(int)));

  QObject::connect(breakPointButton, SIGNAL(clicked()), this, SLOT(breakPointButtonClicked())); // must put utside the scroll signal

  QObject::connect(stepButton, SIGNAL(clicked()), this, SLOT(stepButtonClicked()));
  QObject::connect(continueButton, SIGNAL(clicked()), this, SLOT(continueButtonClicked()));
  QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
  QObject::connect(inspectButton, SIGNAL(clicked()), this, SLOT(inspectButtonClicked()));
  QObject::connect(quitDButton, SIGNAL(clicked()), this, SLOT(quitDButtonClicked()));
  QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}
DebuggerWindow::~DebuggerWindow(){
  
  delete scroll;
  delete backend;

  delete breakPointButton;
  delete continueButton;
  delete stepButton;
  delete nextButton;
  delete inspectButton;
  delete resetButton;

  delete controllerLayout;
  delete quitDButton;

  delete debugLayout;

  delete error;
  delete closeButton;
  delete ErrorLayout;
  delete ErrorWin;

}

// highlight the current line in state
void DebuggerWindow::highlightCurr(){

  QBrush reset(Qt::white);
  currentItem->setBackground(reset);

  QBrush background(Qt::green);

  currentItem = scroll->item(backend->getCurrLine()-1);

  currentItem->setBackground(background);

}

// highlight when the breakpoint is set
void DebuggerWindow::highlightBreakPoint(int i){

  QBrush background(Qt::yellow);

  breakPointHighlight = scroll->item(i);

  breakPointHighlight->setBackground(background);

}

// when selecting the various points
void DebuggerWindow::preBreak(int i){
  breakPoint = i;
}

// when the actual button is clicked, it takes the breakPoint from 
// preBreak to set the breakPoint
// if a breakpoint already exists, then it removes the breakPoint instead
void DebuggerWindow::breakPointButtonClicked(){

  if(backend->breakPointExists(breakPoint)){
    backend->removeBreakPoint(breakPoint);
    QListWidgetItem* resetItem = scroll->item(breakPoint);
    QBrush reset(Qt::white);
    resetItem->setBackground(reset);
  }
  else {
    backend->setBreakPoint(breakPoint);
    highlightBreakPoint(breakPoint);
  }
  
}

void DebuggerWindow::stepButtonClicked(){

  try{
  backend->step();
  highlightCurr();
  }
  catch(std::invalid_argument &e){ // catching if there is a divide by Zero or Illegal Jump
    backend->reset();

    QString temp = "Error - Divide By Zero";
    error->setText(temp);
    ErrorWin->show(); // if there is an error, then the ErrorWin will pop up 

  }
  catch(std::out_of_range &e){
    backend->reset();

    QString temp = "Error - Illegal Jump Instructions";
    error->setText(temp);
    ErrorWin->show();
    
  }

}

void DebuggerWindow::continueButtonClicked(){
  
  try{
    backend->continues();
    highlightCurr();
  }
  catch(std::invalid_argument &e){
    backend->reset();

    QString temp = "Error - Divide By Zero";
    error->setText(temp);
    ErrorWin->show();

  }
  catch(std::out_of_range &e){
    backend->reset();

    QString temp = "Error - Illegal Jump Instructions";
    error->setText(temp);
    ErrorWin->show();

  }
  
}

void DebuggerWindow::nextButtonClicked(){
  
  try{
  backend->next();
  highlightCurr();
  }
  catch(std::invalid_argument &e){
    backend->reset();

    QString temp = "Error - Divide By Zero";
    error->setText(temp);
    ErrorWin->show();

  }
  catch(std::out_of_range &e){
    backend->reset();

    QString temp = "Error - Illegal Jump Instructions";
    error->setText(temp);
    ErrorWin->show();

  }

}

// opens up the ValuesWindow
void DebuggerWindow::inspectButtonClicked(){

  if(inspect == NULL){
    inspect = new ValuesWindow(*backend);
    inspect->show();
  }
  else{
    inspect->show();
  }

}

// resets the Facile
void DebuggerWindow::resetButtonClicked(){
  backend->reset();
  highlightCurr();
}

// ends the application
void DebuggerWindow::quitDButtonClicked(){QApplication::quit();}

// closes the ErrorWin
void DebuggerWindow::closeButtonClicked(){ErrorWin->hide();}