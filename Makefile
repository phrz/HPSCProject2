#
#  Makefile
#  HPSCProject2
#
#  Created by Paul Herz on 10/4/16.
#  Copyright © 2016 Paul Herz. All rights reserved.
#

TARGETA = vandermonde
TARGETB = test_newton
TARGETC = kepler

CXX = g++
CFLAGS = -std=c++14

SRC = src/
LIB = lib/
BIN = bin/
ROOT = $(shell pwd)/
DATA = data/
NB = notebooks/
RP = reports/

AFILES = vandermonde.cpp
BFILES = test_newton.cpp
CFILES = kepler.cpp
LIBFILES = Vector.cpp Matrix.cpp

NOTEBOOK = $(NB)proj2.ipynb
REPORT = $(RP)proj2.pdf



################################
# All target                   #
################################

all: all_bin all_data all_reports



################################
# Application binaries         #
################################

all_bin: $(TARGETA) $(TARGETB) $(TARGETC)

$(TARGETA):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETA) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(AFILES))

$(TARGETB):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETB) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(BFILES))

$(TARGETC):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETC) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(CFILES))



################################
# Data files                   #
################################

all_data: data_a data_b data_c

data_a: $(TARGETA)
	cd $(BIN); ./$(TARGETA) > $(DATA)a_out.txt

data_b: $(TARGETB)
	cd $(BIN); ./$(TARGETB) > $(DATA)b_out.txt

data_c: $(TARGETC)
	cd $(BIN); ./$(TARGETC)



################################
# Reports                      #
################################

all_reports: $(REPORT_A) $(REPORT_B)

$(REPORT): all_data $(NOTEBOOK)
	jupyter nbconvert --to pdf --execute $(NOTEBOOK) --output-dir $(ROOT)$(RP)



################################
# Miscellaneous                #
################################

clean:
	rm -f ./$(DATA)/*
	rm -f ./$(BIN)$(TARGETA)
	rm -f ./$(BIN)$(TARGETB)
	rm -f ./$(BIN)$(TARGETC)
	rm -f ./$(NB)*.nbconvert.ipynb

