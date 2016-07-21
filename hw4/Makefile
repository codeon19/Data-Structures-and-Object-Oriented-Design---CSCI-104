CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: $(BIN_DIR)/Facile $(BIN_DIR)/.dirstamp

$(BIN_DIR)/Facile: Facile.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o $(BIN_DIR)/ProgramState.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/ToStatement.o $(BIN_DIR)/GoSubStatement.o $(BIN_DIR)/ReturnStatement.o $(BIN_DIR)/IfStatement.o lib/Statement.h 
	$(CXX) $(CPPFLAGS) $^ -o $(BIN_DIR)/Facile

$(BIN_DIR)/llistint.o: src/llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/stackint.o: src/stackint.cpp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/stackint.o

$(BIN_DIR)/ProgramState.o: src/ProgramState.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/ProgramState.o

$(BIN_DIR)/LetStatement.o: src/LetStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/LetStatement.o

$(BIN_DIR)/PrintStatement.o: src/PrintStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/PrintStatement.o

$(BIN_DIR)/PrintAllStatement.o: src/PrintAllStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/PrintAllStatement.o

$(BIN_DIR)/AddStatement.o: src/AddStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/AddStatement.o

$(BIN_DIR)/SubStatement.o: src/SubStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/SubStatement.o

$(BIN_DIR)/MultStatement.o: src/MultStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/MultStatement.o

$(BIN_DIR)/DivStatement.o: src/DivStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/DivStatement.o

$(BIN_DIR)/ToStatement.o: src/ToStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/ToStatement.o

$(BIN_DIR)/GoSubStatement.o: src/GoSubStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/GoSubStatement.o

$(BIN_DIR)/ReturnStatement.o: src/ReturnStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/ReturnStatement.o

$(BIN_DIR)/IfStatement.o: src/IfStatement.cpp $(BIN_DIR)/ProgramState.o
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/IfStatement.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp