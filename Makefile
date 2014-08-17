TOPLEVEL ?= $(dir $(lastword $(MAKEFILE_LIST)))
CPPLINT ?= $(TOPLEVEL)/cpplint.py
PYTHON ?= python

SOURCES = \
	examples/async_pi_estimate/addon.cc \
	examples/async_pi_estimate/async.cc \
	examples/async_pi_estimate/async.h \
	examples/async_pi_estimate/pi_est.cc \
	examples/async_pi_estimate/pi_est.h \
	examples/async_pi_estimate/sync.cc \
	examples/async_pi_estimate/sync.h \
	nan.h \
	test/cpp/asyncworker.cpp \
        test/cpp/asyncworkerprogress.cpp \
        test/cpp/asyncworkererror.cpp \
        test/cpp/bufferworkerpersistent.cpp \
        test/cpp/morenews.cpp \
	test/cpp/multifile1.cpp \
	test/cpp/multifile2.cpp \
	test/cpp/multifile2.h \
        test/cpp/news.cpp \
	test/cpp/optionvalues.cpp \
	test/cpp/persistent.cpp \
	test/cpp/returnemptystring.cpp \
	test/cpp/returnnull.cpp \
	test/cpp/returnundefined.cpp \
	test/cpp/returnvalue.cpp \
	test/cpp/settergetter.cpp \
	test/cpp/strings.cpp \
	test/cpp/symbols.cpp \
        test/cpp/weak.cpp \
	node_modules/node-gyp/gyp/data/win/large-pdb-shim.cc

FILTER = -whitespace/parens

.PHONY: lint

lint:
	cd $(TOPLEVEL) && $(PYTHON) $(CPPLINT) --filter=$(FILTER) $(SOURCES)
