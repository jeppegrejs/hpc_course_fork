CXX := clang++
OPT = -O3 -Wall
CXXFLAGS := $(OPT) -Wall -std=c++17 -march=native

PYTHON := /Users/nielsaugustdavidsen/.local/share/mamba/envs/scicompenv/bin/python


# Get pybind11 include flags
INC := $(shell $(PYTHON) -m pybind11 --includes)
# Get Python extension suffix
EXT := $(shell $(PYTHON) -c "from sysconfig import get_config_var; print(get_config_var('EXT_SUFFIX'))")

default: SIR_python

SIR_python: SIR_python.cpp
	$(CXX) SIR_python.cpp -o SIR_python$(EXT) \
		-fPIC -shared $(CXXFLAGS) $(INC) \
		-undefined dynamic_lookup

clean:
	rm -f SIR SIR_python
	rm -f SIR_python$(EXT)
