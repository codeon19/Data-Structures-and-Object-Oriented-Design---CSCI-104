#include "llistint.h"
#include "stackint.h"
#include "gtest/gtest.h"

class llisttest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	llisttest() {
		// You can do set-up work for each test here.
	}

	virtual ~llisttest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		
		// Code here will be called immediately after the constructor (right
		// before each test).
		
		for(int i = 0; i < 5; i++){
			list.insert(i, i);
		}
		
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).

	}

	// Objects declared here can be used by all tests in the test case
	LListInt list;
};

TEST_F(llisttest, copyNominal) {

	LListInt copy(list);

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(list.get(i), i);
	}	

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(copy.get(i), i);
	}
}

TEST_F(llisttest, assignNominal) {

	LListInt assign;

	for(int i = 0; i < 5; i++){
		assign.insert(i, i+1);
	}

	for(int i = 0; i < 5; i++){
		EXPECT_EQ(assign.get(i), i+1);
	}

	assign = list;

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(assign.get(i), i);
	}
}

TEST_F(llisttest, addNominal) {

	LListInt add;

	for(int i = 5; i < 10; i++){
		add.insert(i-5, i);
	}

	list = list + add;

	for (int i = 0 ; i < 10; i++) {
		EXPECT_EQ(list.get(i), i);
	}
}

TEST_F(llisttest, accessNominal) {

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(list[i], i);
	}
}