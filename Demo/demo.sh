#!/bin/bash

cd ..
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
