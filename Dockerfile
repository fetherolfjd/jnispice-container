FROM centos:7 AS base

ARG RUN_TEST="false"
ENV RUN_TEST=${RUN_TEST}

LABEL version.cspice="N0066" \
version.jnispice="2.0.0" \
spice.url="https://naif.jpl.nasa.gov/naif/index.html" \
org.opencontainers.image.authors="Justin D. Fetherolf" \
org.opencontainers.image.source="" \
org.opencontainers.image.title="JNISpice" \
org.opencontainers.image.description="Package JNISpice Java classes, shared object(s), and kernel data into a single JAR for consumption"

RUN mkdir -p /tmp/jnispice && \
mkdir -p /tmp/spice-basic/src/main/java/spice/basic && \
mkdir -p /tmp/spice-basic/src/main/resources/kernels && \
yum install -y java-1.8.0-openjdk-headless maven && \
yum clean all

COPY JNISpice /tmp/jnispice/
COPY pom.xml /tmp/spice-basic/

RUN cp /tmp/jnispice/src/JNISpice/spice/basic/*.java /tmp/spice-basic/src/main/java/spice/basic/ && \
if [ ${RUN_TEST} == "true" ]; then cd /tmp/jnispice/lib; java -cp ../exe:../src/JNISpice/ -Djava.library.path=$(pwd) JNITspice; fi && \
cp /tmp/jnispice/lib/libJNISpice.so /tmp/spice-basic/src/main/resources/ && \
cd /tmp/spice-basic && \
mvn clean install

FROM centos:7
RUN mkdir -p /usr/local/lib/JNISpice/
COPY --from=base /tmp/spice-basic/target/spice-basic-2.0.0.jar /usr/local/lib/JNISpice/
COPY --from=base /tmp/spice-basic/target/spice-basic-2.0.0-sources.jar /usr/local/lib/JNISpice/
