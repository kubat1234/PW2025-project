CXX = g++
CXXFLAGS = -O3 -fopenmp

TARGETS = slow optimized optimized2 thread thread2 omp omp2

INPUT_FILE = test.in
TIME_CMD = time -f "Czas: %es"

SRCS = $(addsuffix .cpp, $(TARGETS))
EXES = $(addsuffix .e, $(TARGETS))
OUTS = $(addsuffix .out, $(TARGETS))

all: run

%.e: %.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

compile: $(EXES)

generate:
	echo "--- Generowanie testów ---"
	python3 testgen.py

run: compile generate
	@echo "--- Rozpoczynanie testów ---"
	@for base_name in $(TARGETS); do \
		echo "--> Uruchamianie $$base_name.e"; \
		$(TIME_CMD) ./$$base_name.e < $(INPUT_FILE) > $$base_name.out; \
		echo "---"; \
	done
	@echo "--- Zakończono wszystkie testy ---"

clean:
	@rm -f $(EXES) $(OUTS) *.in

.phony: all run clean generate compile