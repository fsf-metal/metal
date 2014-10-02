MeTAL: My eTrading Adapters Library
===================================
An Open Source Exchange Connectors library

QuickStart
----------

1) Clone this repository
git clone https://github.com/fsf-metal/metal.git

2) Produce QuickFIX library
For linux: Clone and build QuickFIXEngine
    git clone https://github.com/quickfix/quickfix.git
    cd quickfix
    ./bootstrap
    ./configure
    make

*Copy libquickfix.so.xxx into metal/lib*
    cp src/C++/.lib/libquickfix.so.16.0.1 ../metal/lib/quickfix.so.16


For windows: quickfix.lib is already compiled in ./lib

3) Build MeTAL library
For linux:
    cd metal/src/metal
    scons

For Windows: open metal/src/visual-studio/Metal.sln

4) More documentation is available at http://metal.jollant.net
