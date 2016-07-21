#ifndef DEBUGGERW_H
#define DEBUGGERW_H

#include "Facile.h"

#include "ValuesWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

#include <QListWidget>
#include <QLineEdit>

#include <fstream>
#include <iostream>

using namespace std;

class DebuggerWindow : public QWidget{

Q_OBJECT

public:

	DebuggerWindow(string file);
	~DebuggerWindow();

  void highlightCurr(); 
  void highlightBreakPoint(int i);

	private slots:

  void preBreak(int i);
	void breakPointButtonClicked();

  void stepButtonClicked();
  void continueButtonClicked();
  void nextButtonClicked();
  void inspectButtonClicked();
  void quitDButtonClicked();
  void resetButtonClicked();

  void closeButtonClicked();
  
private:

  string file; // filename

  Facile* backend;

  // To open the ValuesWindow
  ValuesWindow* inspect;

  // DebuggerWindow
	QVBoxLayout* debugLayout;

  QHBoxLayout* controllerLayout;
  	
  QPushButton* breakPointButton;
  QPushButton* stepButton;
  QPushButton* continueButton;
  QPushButton* nextButton;
  QPushButton* inspectButton;
  QPushButton* quitDButton;
  QPushButton* resetButton;

  QListWidget* scroll;

  QLabel* hi;

  int breakPoint;

  QListWidgetItem* currentItem;
  QListWidgetItem* breakPointHighlight;

  // ErrorWin

  QVBoxLayout* ErrorLayout;

  QWidget* ErrorWin;
  QLabel* error;
  QPushButton* closeButton;

};

#endif