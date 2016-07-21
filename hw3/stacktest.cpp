#include "stackint.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class StackIntTest : public testing::Test{

protected:

	StackIntTest() {}
	virtual ~StackIntTest() {}

	virtual void SetUp() {}

	virtual void TearDown(){}

	StackInt stack;

};

TEST_F(StackIntTest, emptyNominal) {

	EXPECT_EQ(stack.empty(), true);

	for (int i = 0; i < 4; i++){
		stack.push(i);
	}

	for (int i = 0; i < 4; i++){
		stack.pop();
	}

	EXPECT_EQ(stack.empty(), true);
}

TEST_F(StackIntTest, pushNominal) {

	for(int i = 0; i < 4; i++){
		stack.push(i);
	}

	EXPECT_EQ(stack.top(), 3);
}

TEST_F(StackIntTest, popNominal) {

	for (int i = 0; i < 4; i++){
		stack.push(i);
	}

	for(int i = 4; i > 0; i--){
		EXPECT_EQ(stack.top(), i-1);
		stack.pop();
	}
}