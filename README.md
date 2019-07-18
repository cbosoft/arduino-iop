# Arduino IOP

Arduino sends data over serial, we read it. We send data over serial, Arduino
reads it. Everybody's happy.


# IOP installation

No dependencies, install the library (shared object) with:

```bash
make
sudo make install
```

To build a basic serial listener, build and install the library then run

```bash
make serlist
```

