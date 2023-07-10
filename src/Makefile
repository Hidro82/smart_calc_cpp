CC = g++
VER = -std=c++17
GCOVFLAGS = -lgtest
GCOVFLAGSLIN = --coverage
GTKFLAG = `pkg-config gtkmm-3.0 --cflags --libs`
ERRFLAGS = -Wall -Werror -Wextra
ILLEGAL = -D private=public
#ASAN = -fsanitize=address
FLAGC = -c
FLAGO = -o
TEST_C = Tests/tests.cc
mafs_C = model/*.cc
mafs_H = model/*.h
calc_C = controller/*.cc
calc_H = controller/*.h
calc_GCDA = covers/*.gcda
gui_C = view/*.cc
gui_H = view/*.h
lib_worker = -Lmodel -l:mafs.a -Lcontroller -l:calc.a

all: install

install: uninstall
	mkdir ready_to_go
	$(CC) $(VER) $(ASAN) $(mafs_C) $(calc_C) $(gui_C) $(FLAGO) ready_to_go/smart_calc $(GTKFLAG)

uninstall: clean
	rm -rf ready_to_go

dist:
	tar -czvf smart_calc.tar.gz ready_to_go

dvi:
	open ref_doc.pdf	

run:
	./ready_to_go/smart_calc

clean:
	rm -rf calc_test a.out
	rm -rf covers html
	rm -rf smart_calc.tar.gz
	rm -rf *.gcno
	rm -rf *.gcov

tests: clean 
	$(CC) $(VER) $(ASAN) $(ERRFLAGS) $(GCOVFLAGSLIN) $(mafs_C) $(calc_C) $(TEST_C) $(FLAGO) calc_test $(GCOVFLAGS)
	./calc_test
	mkdir covers
	mv *.gcda covers
	mv *.gcno covers

gcov_report: tests
	mkdir html
	gcov $(calc_GCDA)
	gcovr
	gcovr --html-details html/coverage.html
	mv *.gcov covers
	open html/coverage.html


check:
	cp ../materials/linters/.clang-format ../src
	clang-format -n $(calc_C) $(calc_H) $(gui_C) $(gui_H) $(TEST_C) $(mafs_C) $(mafs_H)
	rm .clang-format
#	$(CC) $(VER) $(ERRFLAGS) $(mafs_C) $(calc_C) $(TEST_C) $(GCOVFLAGS)
#	valgrind --leak-check=full ./a.out
#	CK_FORK=no leaks --atExit -- ./a.out
