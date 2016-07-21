# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files

# uncomment this to compile llisttest
# llisttest: llisttest.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
		# $(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

# uncomment this to compile stacktest
# stacktest: stacktest.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
	# $(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

arithmetic: arithmetic.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ -o $@	
$(BIN_DIR)/llistint.o: llistint.cpp llistint.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@
$(BIN_DIR)/stackint.o: stackint.cpp stackint.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@
# $(BIN_DIR)/arithmetic.o: arithmetic.cpp $(BIN_DIR)/.dirstamp
	# $(CC) $(CPPFLAGS) -c $< -o $@
$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $@

.PHONY: clean

clean: 
	rm -rf $(BIN_DIR)
