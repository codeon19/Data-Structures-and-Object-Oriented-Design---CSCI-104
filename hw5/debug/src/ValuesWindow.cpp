#include "../lib/ValuesWindow.h"
#include "../lib/Facile.h"

#include "../lib/msort.h"

#include <string>

#include <iostream>

// different comparators used for the 4 different options
struct nameAscending {
    
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) 
    { 
      string left = lhs.first;
      string right = rhs.first;

      if(left.compare(right) < 0){
      	return true;
      }
      else{
      	return false;
      }
    }

};

struct nameDescending {
    
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) 
    { 
    	string left = lhs.first;
      	string right = rhs.first;

      	if(left.compare(right) > 0){
      		return true;
      	}
      	else{
      		return false;
      	}
      
    }

};

struct IntAscending {
    
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) 
    { 
      return lhs.second < rhs.second; 
    }

};

struct IntDescending {
	
	bool operator()(const pair<string, int> &lhs, const pair<string, int> &rhs)
	{
		return lhs.second > rhs.second;
	}
};

ValuesWindow::ValuesWindow(Facile &bk): QWidget(NULL) {

	backend = &bk; // pointer to the Facile object passed

	ordering = 0;

	valuesWindowLayout = new QVBoxLayout;

	displayData = new QListWidget;

	updateButtonClicked(); // setting namesAscending as the default

	valuesWindowLayout->addWidget(displayData);

	controllerLayout = new QHBoxLayout;

	options = new QComboBox(); // holding the different options avaliable

	options->addItem("Ascending Names");
	options->addItem("Descending Names");
	options->addItem("Ascending Values");
	options->addItem("Descending Values");

	controllerLayout->addWidget(options);

  	updateButton = new QPushButton("Update");
  	controllerLayout->addWidget(updateButton);

  	valuesWindowLayout->addLayout(controllerLayout);

  	closeButton = new QPushButton("Close");
  	valuesWindowLayout->addWidget(closeButton);

  	setLayout(valuesWindowLayout);

  	QObject::connect(options, SIGNAL(activated(int)), this, SLOT(optionsButtonClicked(int)));
  	QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
  	QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));


}
ValuesWindow::~ValuesWindow(){

	delete displayData;

	delete options;

	delete updateButton; 
	delete closeButton;

	delete controllerLayout;

	delete valuesWindowLayout;
}

void ValuesWindow::optionsButtonClicked(int i){

	ordering = i; // setting the option
}

void ValuesWindow::updateButtonClicked(){

	displayData->clear(); // clearing the current ordering 

	vector<pair<string, int> > pairs = backend->getPairs(); // getting the different pairs from the Facile object

	if(ordering == 0){
		nameAscending compare;
		mergeStart(pairs, compare); // mergesorting
	}
	else if(ordering == 1){
		nameDescending compare;
		mergeStart(pairs, compare);
	}
	else if(ordering == 2){
		IntAscending compare;
		mergeStart(pairs, compare);
	}
	else{
		IntDescending compare;
		mergeStart(pairs, compare);
	}

	for(int i = 0; i < pairs.size(); i++){
	stringstream ss; 
	ss << pairs[i].second;
	string value = ss.str();

	string reordering = pairs[i].first + " " + value;

    displayData->addItem(QString::fromStdString(reordering)); // adding in the new ordering 
  	}

}

// closing the ValuesWindow 
void ValuesWindow::closeButtonClicked(){hide();}