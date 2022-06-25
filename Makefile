.PHONY: all run tests clean cpplint install uninstall dist dvi gcov_report

CC=g++
GTEST_FLAG=-lgtest
CHECK_FLAGS=-Wall -Werror -Wextra
LINUX_FLAGS= -lm -lsubunit -lrt -lpthread
OS:=$(shell uname -s)
PROJECT_NAME=s21_SmartCalc_v2
MODEL_SRC= $(PROJECT_NAME)/Model/*/*.cpp $(PROJECT_NAME)/Model/*.cpp

SOURCES=$(PROJECT_NAME)/Model/model.cpp \
		$(PROJECT_NAME)/Model/date.cpp \
		$(PROJECT_NAME)/Model/additionalmodel.cpp \
		$(PROJECT_NAME)/Model/SimpleCalcModel/parsermodel.cpp \
		$(PROJECT_NAME)/Model/SimpleCalcModel/simplecalcmodel.cpp \
		$(PROJECT_NAME)/Model/CreditCalcModel/creditcalcmodel.cpp \
		$(PROJECT_NAME)/Model/DepositCalcModel/depositcalcmodel.cpp \
		$(PROJECT_NAME)/View/mainview.cpp \
		$(PROJECT_NAME)//View/addpaymentview.cpp \
		$(PROJECT_NAME)/View/s21_converts.cpp \
		$(PROJECT_NAME)/View/SimpleCalcView/simplecalcview.cpp \
		$(PROJECT_NAME)/View/GraphCalcView/graphcalcview.cpp \
		$(PROJECT_NAME)/View/CreditCalcView/creditcalcview.cpp \
		$(PROJECT_NAME)/View/DepositCalcView/depositcalcview.cpp \
		$(PROJECT_NAME)/View/TableView/tableview.cpp \
		$(PROJECT_NAME)/View/TableView/tablewidget.cpp \
		$(PROJECT_NAME)/Controller/controller.cpp \
		$(PROJECT_NAME)/main.cpp 

HEADERS=$(PROJECT_NAME)/Model/model.h \
		$(PROJECT_NAME)/Model/date.h \
		$(PROJECT_NAME)/Model/additionalmodel.h \
		$(PROJECT_NAME)/Model/SimpleCalcModel/parsermodel.h \
		$(PROJECT_NAME)/Model/SimpleCalcModel/simplecalcmodel.h \
		$(PROJECT_NAME)/Model/CreditCalcModel/creditcalcmodel.h \
		$(PROJECT_NAME)/Model/DepositCalcModel/depositcalcmodel.h \
		$(PROJECT_NAME)/View/mainview.h \
		$(PROJECT_NAME)/View/addpaymentview.h \
		$(PROJECT_NAME)/View/s21_converts.h \
		$(PROJECT_NAME)/View/SimpleCalcView/simplecalcview.h \
		$(PROJECT_NAME)/View/GraphCalcView/graphcalcview.h \
		$(PROJECT_NAME)/View/CreditCalcView/creditcalcview.h \
		$(PROJECT_NAME)/View/DepositCalcView/depositcalcview.h \
		$(PROJECT_NAME)/View/TableView/tableview.h \
		$(PROJECT_NAME)/Controller/controller.h

all: run

run: install
	@cd ~/Applications/$(PROJECT_NAME).app/Contents/MacOS && ./$(PROJECT_NAME)

install:
	@cd $(PROJECT_NAME) && qmake -o Makefile $(PROJECT_NAME).pro && make install

uninstall:
	@rm -rf ~/Applications/$(PROJECT_NAME).app

tests: unit_test
	./test

unit_test:
	@rm -rf test
ifeq ($(OS), Darwin)
	$(CC) $(CHECK_FLAGS) $(MODEL_SRC) tests.cpp -o test $(GTEST_FLAG)
else
	$(CC) $(CHECK_FLAGS) $(MODEL_SRC) tests.cpp -o test $(GTEST_FLAG) $(LINUX_FLAGS)
endif

gcov_report:
	@$(CC) $(CHECK_FLAGS) --coverage $(MODEL_SRC) tests.cpp -o test $(GTEST_FLAG)
	@./test
	@lcov -t test -o test.info -c -d ./
	@genhtml -o report test.info
	@open report/index.html

clean: uninstall
	@rm -rf *.o *.gcno *gcda *.info report *.tar *.html test $(PROJECT_NAME)/s21_SmartCalc_v2.app
	@cd $(PROJECT_NAME) && make clean

dvi:
	@pandoc readme.md -o dvi.html
	@open dvi.html

dist:
	@tar -cf $(PROJECT_NAME).tar $(SOURCES) $(HEADERS) Makefile readme.md

cpplint:
	@python3 ../materials/linters/cpplint.py --extensions=cpp $(SOURCES) $(HEADERS)
	
leaks: unit_test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test $(GTEST_FLAG) $(LINUX_FLAGS)
endif

