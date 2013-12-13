SRC		= src
TEST_SRC	= test
BUILD		= build
BUILD_TEST	= $(BUILD)/test
BUILD_NUMBER	?= '"dev"'
LIB_PATH = /usr/local/lib
#LT = dylib
LT = a

LIBS		= \
			$(LIB_PATH)/libboost_filesystem-mt.$(LT) 	\
			$(LIB_PATH)/libboost_system-mt.$(LT) 		\
			$(LIB_PATH)/libboost_program_options-mt.$(LT)	\
			$(LIB_PATH)/libboost_regex-mt.$(LT)

TEST_LIBS	= 	$(LIB_PATH)/libboost_unit_test_framework-mt.$(LT)

OBJECTS 	=	


TEST_OBJECTS	=	$(BUILD_TEST)/test_main.o		\
			$(BUILD_TEST)/no_arguments_tests.o	\
			$(BUILD_TEST)/switch_argument_tests.o	\
			$(BUILD_TEST)/value_argument_no_default_tests.o \
			$(BUILD_TEST)/raises_exception_on_invalid_argument_tests.o \
			$(BUILD_TEST)/filename_argument_tests.o

all		:	build/app test

$(BUILD)	:
	-mkdir $@

$(BUILD_TEST)		:	$(BUILD)
	-mkdir $@

$(BUILD)/app		:	$(BUILD) $(OBJECTS) $(BUILD)/main.o
	clang++ -g -O1 -o $@ -std=c++11 -D BUILD_NUMBER=$(BUILD_NUMBER) -Xclang "-stdlib=libc++" -lc++ $(SRC)/*.cpp -I /usr/local/include $(LIBS)

$(BUILD)/apptest	:	$(OBJECTS) $(TEST_OBJECTS)
	clang++ $^ -o $@ -std=c++11 -lc++ $(LIBS) $(TEST_LIBS)


test			:	$(BUILD_TEST) $(BUILD)/apptest
	./$(BUILD)/apptest


ci-test: $(BUILD)/apptest
	./$^ --log_format=XML --log_sink=results.xml --log_level=all --report_level=no

ci-build:	clean $(BUILD)/app $(BUILD_TEST) ci-test



clean:
	-rm -rf $(BUILD)/*
	-rm results.xml

$(BUILD)/%.o : $(SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD)/%.o : $(SRC)/%.c
	clang -g -O1 -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD_TEST)/%.o : $(TEST_SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -D MAKEFILE_BUILD -c $< -o $@


