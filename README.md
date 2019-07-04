## Introduction
SystemC is a modelling and simulation language especially for the development of complex electronic systems comprising both hardware and software components.

SystemC AMS is an extension to SystemC for Analog/Mixed-Signal (AMS) systems. 

This repository contains some simple examples. Examples 01-03 only use SystemC, examples 04 and 05 both use SystemC and Systemc AMS

#### Examples:
1. Up-down counter with overflow and underflow interrupt
2. Arithmetic Logic Unit (ALU)
3. Generic FIFO
4. Control system of DC motor with proportional-integrate-derivative (PID) controller and pulse-width modulator (PWM)
5. Electronic Control Unit (ECU) for configuration of the PID of example 04

## Requirements
* CMake v3.5+
* A c++ compiler (gcc)
* make
* SystemC and SystemC AMS

## Installation on Ubuntu
* SystemC
```
$ apt-get -qq install build-essential wget
$ wget http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.2.tar.gz
$ tar -xzf systemc-2.3.2.tar.gz
$ cd systemc-2.3.2
$ mkdir objdir && cd objdir
$ ../configure --prefix=/usr/local/systemc-2.3.2/
$ make
$ make install
```
* SystemC AMS

Download SystemC AMS 2.1 at http://www.coseda-tech.com/systemc-ams-proof-of-concept
```
$ tar -xzf systemc-ams-2.1.tar.gz
$ cd systemc-ams-2.1
$ mkdir objdir && cd objdir
$ ../configure --prefix=/usr/local/systemc-ams-2.1/ --with-systemc=/usr/local/systemc-2.3.2
```
SystemC AMS is not compiling out of the box. By editing two files with the following commands you can fix this easily.
```
$ sed -i '41i\''\n#include <cstring>\n' /systemc-ams-2.1/src/scams/impl/predefined_moc/tdf/sca_tdf_ct_vector_ss_proxy.h
$ sed -i '41i\''\n#include <cstring>\n' /systemc-ams-2.1/src/scams/impl/predefined_moc/tdf/sca_tdf_ct_ltf_nd_proxy.h
```
```
$ make
$ make install
```

* CMake
```
$ apt-get install cmake
```

## Docker
Docker containers with all requirements help make testing the examples easier.

Download SystemC AMS 2.1 at http://www.coseda-tech.com/systemc-ams-proof-of-concept and copy it to the base directory. Run from base directory

```
docker build -t systemc .
```

Testing the examples: Build and run the respective docker containers in its folders.
