# JNISpice Container

An unofficial GitHub presence of JPL NAIF's SPICE library. Visit [the NAIF website](https://naif.jpl.nasa.gov/naif/index.html)
for more information to include other source code, tutorials, data, bugs, etc.

The two JNISpice archives included in this repository are designated for Mac OS X 64 bit, and Linux 64 bit.
Others are available from the NAIF website, but I have no need for them at this time, and thus have not included them.
This container will unpack each archive and copy the shared library
directly. NAIF specifically discourages attempting to build from source due to differences
in compilers and libraries, though that could theoretically be done here.

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

The idea here is to package the Java artifacts, shared libraries, and kernel data into
a single JAR file for easier consumption in Java applications.

## What about more kernels?

At the time of this writing, the single file in the kernels directory is all that I need.

## What else?

I chose to give the JAR the group ID "spice.basic" and the artifact ID "spice-basic". I'm not convinced it's a great idea to publish the JARS to Maven Central or anything, so please don't.
I would think it's fair game to publish to a private repository though.
