ARG JAVA_VERSION=8
ARG MAVEN_VERSION=3.5.0

FROM maven:${MAVEN_VERSION}-jdk-${JAVA_VERSION} AS base

LABEL version.cspice="N0066" \
version.jnispice="2.0.0" \
spice.url="https://naif.jpl.nasa.gov/naif/index.html" \
org.opencontainers.image.authors="Justin D. Fetherolf" \
org.opencontainers.image.source="https://github.com/fetherolfjd/jnispice-container" \
org.opencontainers.image.title="JNISpice JAR" \
org.opencontainers.image.description="Package JNISpice Java classes, shared object(s), and kernel data into a single JAR for consumption"

ENV SPC_PKGS_DIR=/tmp/jnispice-packages
ENV SPC_J_DEST_DIR=/tmp/spice-basic/src/main/java/spice/basic
ENV SPC_RES_DEST_DIR=/tmp/spice-basic/src/main/resources

RUN mkdir -p ${SPC_PKGS_DIR} && \
mkdir -p ${SPC_J_DEST_DIR} && \
mkdir -p ${SPC_RES_DEST_DIR}/kernels

COPY jnispice-packages/ ${SPC_PKGS_DIR}
COPY pom.xml /tmp/spice-basic/
COPY kernels/ ${SPC_RES_DEST_DIR}/kernels
COPY configure.sh /tmp/

RUN /tmp/configure.sh
WORKDIR /tmp/spice-basic
RUN mvn clean install

FROM centos:7
RUN mkdir -p /usr/local/lib/JNISpice/
COPY --from=base /tmp/spice-basic/target/spice-basic-2.0.0.jar /usr/local/lib/JNISpice/
COPY --from=base /tmp/spice-basic/target/spice-basic-2.0.0-sources.jar /usr/local/lib/JNISpice/
