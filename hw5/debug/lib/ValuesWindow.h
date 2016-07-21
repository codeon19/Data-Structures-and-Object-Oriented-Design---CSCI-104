#ifndef VALWINDOW_H
#define VALWINDOW_H

#include "Facile.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

#include <QListWidget>
#include <QComboBox>

using namespace std;

class ValuesWindow : public QWidget{

Q_OBJECT

public:

	ValuesWindow(Facile &bk); // takes in the Facile object passed to the ValuesWindow
	~ValuesWindow();

	private slots:

	void optionsButtonClicked(int i); 
	void updateButtonClicked();
	void closeButtonClicked();

private:

	QVBoxLayout* valuesWindowLayout;

	QListWidget* displayData;

	QHBoxLayout* controllerLayout;

	QComboBox* options;

	QPushButton* updateButton;
 	QPushButton* closeButton;

 	Facile* backend; // pointing to the reference object passed 

 	int ordering; 

};

#endif