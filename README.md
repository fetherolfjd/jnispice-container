# JNISpice Container

An unofficial GitHub presence of JPL NAIF's SPICE library. Visit [the NAIF website](https://naif.jpl.nasa.gov/naif/index.html)
for more information to include other source code, tutorials, data, bugs, etc.

The JNISpice Toolkit code included in this repository is designated as a build for
"PC Linux GCC Java 1.5 64-bit". This container currently copies the downloaded shared library
directly. NAIF specifically discourages attempting to build from source due to differences
in compilers and libraries.

## Disclaimer

The folks at NAIF explicitly state:

> This protoype JNISpice system is available to the NAIF team and volunteer testers to
> enable experimentation and review, with the aim of finalizing the specification
> and design of the system.
>
> ...
>
> This prototype system is at an "alpha test" level of maturity.

So, use this and/or JNISpice directly at your own risk.

## What is this then?

The idea here is to package the Java artifacts, shared library, and kernel data into
a single JAR file for easier consumption in Java applications.

## What about more kernels?

At the time of this writing, the single file in the kernels directory is all that
I need.
