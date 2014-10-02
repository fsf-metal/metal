# MeTAL: My eTrading Adapters Library
An Open Source Exchange Connectors library

## QuickStart

### 1) Clone this repository<br>
`git clone https://github.com/fsf-metal/metal.git`

### 2) Get QuickFIX library<br>
#### For Linux:<br> 
*Clone and build QuickFIXEngine*<br>
`    git clone https://github.com/quickfix/quickfix.git`<br>
`    cd quickfix`<br>
`    ./bootstrap`<br>
`    ./configure`<br>
`    make`<br>

*Copy libquickfix.so.xxx into metal/lib*<br>
`    cp src/C++/.lib/libquickfix.so.16.0.1 ../metal/lib/quickfix.so.16`


#### For Windows:<br>
*quickfix.lib is already compiled in ./lib*

### 3) Build MeTAL library<br>
#### For linux:<br>
`    cd metal/src/metal`<br>
`    scons`<br>

#### For Windows: <br>
*Open metal/src/visual-studio/Metal.sln*

### 4) More documentation<br>
Documentation is available at http://metal.jollant.net
