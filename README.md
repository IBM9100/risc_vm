# A RISC Virtual Machine

This is an implementation of [LC-3](https://en.wikipedia.org/wiki/LC-3) [RISC](https://en.wikipedia.org/wiki/Reduced_instruction_set_computer) virtual machine.

Most of the instruction set is implemented, as well as the interrupt service routines necessary for an operating system, but full interrupt handling is not supported.

![2048](https://i.loli.net/2020/12/16/nFROtGe7T8Ibo6h.png)

## Building
#### Requires
* Linux kernel version >= 2.6.28
* GCC >= 4.7
* cmake >= 3.4.1

```bash
# Debian, Ubuntu, etc.
$ sudo apt-get install build-essential cmake make
# CentOS
$ sudo yum install gcc cmake make
```

#### Tested on
* wsl Linux 4.4.0
* ubuntu 16.0.4

### Now you can start compiling
```bash
$ git clone https://github.com/IBM9100/risc_vm.git
$ cd risc_vm && mkdir build && cd build
$ cmake ..
$ make
```
You can load the sample program provided in example.

```bash
$ ./riscvm 2048.obj
```


## Credits
Thanks for their teaching:

@Justin Meiners, @dokidoki_2 NPU, @Y. Xiang THU.

## License
MIT License

Copyright (c) 2019 NAGATOYUKI/IBM9100

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## References
[1] https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf - The Instruction Set Architecture (ISA) of the LC-3 specification document.

[2] https://justinmeiners.github.io/lc3-vm - A virtual machine implementation tutorial

[3] https://github.com/rpendleton/lc3-2048 - Implementation of git.io/2048 written in LC-3 assembly

[4] https://github.com/justinmeiners/lc3-rogue - Roguelike tunnel generator in LC-3 assembly