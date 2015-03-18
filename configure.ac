# Thx @ https://github.com/roryyorke/swig-python-autotools-example

# typical init
AC_INIT([ConnectFourAILib],[1.0])

# foreign: non-GNU, don't check for NEWS, AUTHORS, etc.
AM_INIT_AUTOMAKE([foreign no-define])

# ask autotools to put extra macros in m4/
AC_CONFIG_MACRO_DIR([m4])

AM_PATH_PYTHON
AX_PYTHON_DEVEL

# http://www.gnu.org/software/autoconf-archive/ax_pkg_swig.html
AX_PKG_SWIG([], [], [ AC_MSG_ERROR([SWIG is required to build.]) ])
AX_SWIG_PYTHON

# Use libtool to link libraries and modules
LT_INIT

AC_PROG_CXX
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
