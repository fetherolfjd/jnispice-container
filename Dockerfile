FROM centos:7

RUN mkdir -p /tmp/jnispice && \
mkdir -p /tmp/spice-basic/src/main/java/spice/basic && \
mkdir -p /tmp/spice-basic/src/main/resources/kernels && \
yum install -y tcsh gcc java-1.8.0-openjdk-headless maven && \
yum clean all

COPY JNISpice /tmp/jnispice/
COPY pom.xml /tmp/spice-basic/

RUN cp /tmp/jnispice/src/JNISpice/spice/basic/*.java /tmp/spice-basic/src/main/java/spice/basic/ && \
cd /tmp/jnispice && \
/bin/tcsh -c "./makeall.csh" && \
cd src/JNISpice && \
/bin/tcsh -c "./mkprodct.csh" && \
cd /tmp/jnispice && \
cp lib/libJNISpice.so /tmp/spice-basic/src/main/resources/ && \
cd /tmp/spice-basic && \
mvn clean install
