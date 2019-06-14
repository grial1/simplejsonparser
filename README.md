# simplejsonparser
[![Code Quality: Cpp](https://img.shields.io/lgtm/grade/cpp/github/grial1/simplejsonparser.svg?color=yellow&style=flat-square)
[![Total Alerts](https://img.shields.io/lgtm/alerts/github/grial1/simplejsonparser.svg?label=lgtm%20alerts&style=flat-square)]

C++ library for parsing simple (non-nested) JSON encoded strings. The code in this repo. is part of the implementation of a light stream processing application to analyze system's logs (some kind of HIDS) that is currently in development.

## Requirements

* __OS Used in development__: Ubuntu 18.04

* __Additional system information__: Linux 4.18.0-21-generic #22~18.04.1-Ubuntu SMP Thu May 16 15:07:19 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux

__UNTIL FURTHER NOTICE, TRY IT WITH THE FOLLOWING COMANDS__:
```
    # The following commands were used in an Ubuntu shell
    $ sudo apt-get install -y build-essential 
    $ make
    $ make run

    # To run the example.cc source with gdb, try the following:
    $ make debug

    # To run the tests, try the following:
    $ make test
```
