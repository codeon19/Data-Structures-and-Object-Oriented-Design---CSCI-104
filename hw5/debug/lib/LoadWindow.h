#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include "DebuggerWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <fstream>
#include <iostream>

class LoadWindow : public QWidget {
  
Q_OBJECT

public:

	LoadWindow();
	~LoadWindow();

	private slots:

	void loadButtonClicked();
	void quitButtonClicked();

	void closeButtonClicked();

private:

	QVBoxLayout* mainLayout;
	QHBoxLayout* loadButtonLayout;

	QLabel* instructions; 
  	
  QLineEdit* fileName;
  	
  QPushButton* loadButton;
  QPushButton* quitButton;

  DebuggerWindow* debug;

  // for the ErrorWin
  QVBoxLayout* ErrorLayout;

  QWidget* ErrorWin;
  QLabel* error;
  QPushButton* closeButton;

};
#endif