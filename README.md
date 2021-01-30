# Arduino Focuser
Custom INDI driver for custom Arduiono focuser

based on https://github.com/indilib/docs/tree/master/drivers/examples/indi_dummy_focuser

# Builoding

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ../
make
sudo make install
```
