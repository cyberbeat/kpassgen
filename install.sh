#!/bin/sh

BUILD=build

mkdir -p $BUILD
cd $BUILD || exit 1
cmake .. -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` || exit 1
make || exit 1
sudo make install || exit 1
kbuildsycoca4
