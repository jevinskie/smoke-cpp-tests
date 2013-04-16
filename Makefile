ifeq ($(PLATFORM), )
	PLATFORM=$(shell uname -s | sed -e "s/CYGWIN.*/Windows/" | sed -e "s/Darwin/Mac/")
endif

ifeq ($(PLATFORM), Windows)
	CC1=cl -nologo -GR- -O2 -c -Fo
	OBJ1=obj
	LINK=link $(LDFLAGS) -nologo libcmt.lib libcpmt.lib -debug -incremental:no -out:
else
	CC1=g++ -c -o
	OBJ1=o
	LINK=g++ -o
endif

CC2=$(CC1)
OBJ2=$(OBJ1)
LDFLAGS=
RM_F=rm -f

ALL_TEST_TARGETS=$(patsubst %.cpp,run_%_1_test,$(wildcard *.cpp)) \
                 $(patsubst %.cpp,run_%_2_test,$(wildcard *.cpp))

ifeq ($(TEST_FILTER), )
  RUN_TEST_TARGETS=$(ALL_TEST_TARGETS)
else
  SELECT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),$(v),))
  RUN_TEST_TARGETS=$(call SELECT,$(TEST_FILTER), $(ALL_TEST_TARGETS))
endif

all: run_all_tests
.PHONY: all

clean:
	$(RM_F) *.pdb *.ilk *.exe *.obj *.obj-* *.o *.o-* dev_null
.PHONY: clean

run_%_test: %_test.exe
	### Running $< ###
	@ ./$< || (echo "### FAIL: $< ###############" && false)
	#     OK: $<
.PHONY: run_%_test

%_1_test.exe: %_1_1.$(OBJ1) %_1_2.$(OBJ2)
	$(LINK)$@ $^

%_2_test.exe: %_2_1.$(OBJ1) %_2_2.$(OBJ2)
	$(LINK)$@ $^

CAT= |& cat
CAT=

%_1_1.$(OBJ1): %.cpp
	$(CC1)$@ -DCONFIG_1 $^ $(CAT)

%_1_2.$(OBJ2): %.cpp
	$(CC2)$@ $^ $(CAT)

%_2_1.$(OBJ1): %.cpp
	$(CC1)$@ $^ $(CAT)

%_2_2.$(OBJ2): %.cpp
	$(CC2)$@ -DCONFIG_1 $^ $(CAT)


run_all_tests: $(RUN_TEST_TARGETS)
	@echo "========================================"
	@echo "ALL TESTS PASSED!"
