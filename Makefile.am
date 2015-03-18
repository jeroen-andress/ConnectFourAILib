# Automake file.  Run ./autogen.sh to generate Makefile.in, etc.

# Use the m4/ directory for macros
ACLOCAL_AMFLAGS = -I m4

## This is the "plain C" ConnectFourAI library
# The library we'll create
lib_LTLIBRARIES = libConnectFourAI.la
# it's source files
libConnectFourAI_la_SOURCES = src/ConnectFourPlayboard.cpp src/ConnectFourPlayerHuman.cpp src/ConnectFourPlayerInterface.cpp src/ConnectFourPlayerMinimaxAlphaBeta.cpp src/ConnectFourPlayerMinimax.cpp 

## This is the Python module interfacing to libConnectFourAI
# ConnectFourAI.py and ConnectFourAIPythonWrap.c are created by SWIG from ConnectFourAI.i
# Put these in the build tree
BUILT_SOURCES = $(builddir)/ConnectFourAI.py $(builddir)/ConnectFourAIPythonWrap.cpp
# tell Make how to create the generated SWIG files
$(builddir)/ConnectFourAI.py $(builddir)/ConnectFourAIPythonWrap.cpp: src/ConnectFourAI.i
	$(SWIG) $(AX_SWIG_PYTHON_OPT) -c++ -o $@ $<

# Ask autotools to install the generated Python file
python_PYTHON = $(builddir)/ConnectFourAI.py
# This is the Python module
pyexec_LTLIBRARIES = _ConnectFourAI.la
# It is composed of the generated C file
_ConnectFourAI_la_SOURCES = $(builddir)/ConnectFourAIPythonWrap.cpp src/ConnectFourAI.i

# -module tells libtool we don't need a 'lib' prefix
_ConnectFourAI_la_LDFLAGS = -module ${PYTHON_LDFLAGS}

# One point of this ConnectFourAI is to have the Python module
# link to another library
_ConnectFourAI_la_LIBADD = libConnectFourAI.la

_ConnectFourAI_la_CPPFLAGS = -I$(srcdir)/src ${PYTHON_CPPFLAGS}
