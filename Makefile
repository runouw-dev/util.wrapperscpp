.PHONY: clean

lazy_test.out: lazy_test.cpp
	$(CXX) -std=c++14 -o $@ $<

clean:
	rm -fv lazy_test.out
