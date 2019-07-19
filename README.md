# Arduino IOP

Arduino sends data over serial, we read it. We send data over serial, Arduino
reads it. Everybody's happy. 🙂


# IOP installation (`c` only)

## `c` projects

No installation necessary! To use in a `c` project, copy-paste the two files (`ardiop.c`
and `ardiop.h`) into your project.

## otherwise

If you're not using `c`, you can link your program against a shared library
`libardiop.so`, which you can build using

```bash
make
sudo make install
```

Then link with `-lardiop`. For example:

```bash
gcc main.c -o arduino_listener -lardiop
```

# Reference implementation

Included in this repository is a reference program which uses the library above.
It simply listens on a serial port for output from the attached Arduino. To
build, run:

```bash
make serlist
```

