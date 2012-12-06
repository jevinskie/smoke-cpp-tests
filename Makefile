CC1=cl -nologo -c -Fo
CC2=$(CC1)
OBJ1=obj
OBJ2=obj
LDFLAGS=
LINK=link $(LDFLAGS) -nologo libcmt.lib libcpmt.lib -debug -incremental:no -out:

RUN_TEST_TARGETS=$(patsubst %.cpp,run_%_1_test,$(wildcard *.cpp)) \
                 $(patsubst %.cpp,run_%_2_test,$(wildcard *.cpp))

all: run_all_tests
.PHONY: all

clean:
	rm -f *.pdb *.ilk *.exe *.obj *.obj-* *.o *.o-* dev_null
.PHONY: clean

run_%_test: %_test.exe
	### Running $< ###
	@ ./$< || ! echo "### FAIL: $< ###############"
	#     OK: $<
.PHONY: run_%_test

%_1_test.exe: %_1_1.$(OBJ1) %_1_2.$(OBJ2)
	$(LINK)$@ $^

%_2_test.exe: %_2_1.$(OBJ2) %_2_2.$(OBJ1)
	$(LINK)$@ $^

%_1_1.$(OBJ1): %.cpp
	$(CC1)$@ -DCONFIG_1 $^ >dev_null

%_1_2.$(OBJ2): %.cpp
	$(CC2)$@ $^ >dev_null

%_2_1.$(OBJ2): %.cpp
	$(CC1)$@ $^ >dev_null

%_2_2.$(OBJ1): %.cpp
	$(CC2)$@ -DCONFIG_1 $^ >dev_null


run_all_tests: $(RUN_TEST_TARGETS)
	@echo "========================================"
	@echo "ALL TESTS PASSED!"
