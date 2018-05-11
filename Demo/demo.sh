#!/bin/bash

cd ..

if [ ! -f m4/ax_swig_python.m4 ]; then
    echo "Download ax_swig_python.m4 ..."
    wget -O m4/ax_swig_python.m4 "http://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_swig_python.m4"
fi

if [ ! -f m4/ax_python_devel.m4 ]; then
    echo "Download ax_python_devel.m4 ..."
    wget -O m4/ax_python_devel.m4 "http://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_python_devel.m4"
fi

if [ ! -f m4/ax_pkg_swig.m4 ]; then
    echo "Download ax_pkg_swig.m4 ..."
    wget -O m4/ax_pkg_swig.m4 "http://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_pkg_swig.m4"
fi

set -e
INSTALLROOT=$PWD/install-root
rm -rf build $INSTALLROOT
libtoolize --force --copy --install
aclocal && autoconf && automake --add-missing
mkdir build
cd build
../configure --prefix=$INSTALLROOT
make
make install
export PYTHONPATH=$(dirname $(find $INSTALLROOT -name ConnectFourAI.py -print))
cd ../Demo
python main.py
