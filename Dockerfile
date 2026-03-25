FROM ubuntu:22.04

ARG USER_ID
ARG GROUP_ID

RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

ENV DEBIAN_FRONTEND=noninteractive

#######################
# Project dependencies
#######################
# General
RUN apt-get update && apt-get install -y \
            cmake \
            git \
            build-essential \
            valgrind \
            cppcheck \
            wget \
            software-properties-common

# clang-format & clang-tidy
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
RUN apt-add-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main"
RUN apt-get update
RUN apt-get install -y clang-15 \
                       clang-format-15 \
                       clang-tidy-15

# Google Test
RUN git clone -q https://github.com/google/googletest.git /googletest \
  && mkdir -p /googletest/build \
  && cd /googletest/build \
  && cmake .. && make && make install \
  && cd / && rm -rf /googletest


# CppCheck
RUN git clone https://github.com/danmar/cppcheck.git /tmp/cppcheck \
    && cd /tmp/cppcheck \
    && git checkout 2.18.3 \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
    && make \
    && make install \
    && rm -rf /tmp/cppcheck

# Google Benchmark
RUN git clone -q https://github.com/google/benchmark.git /tmp/benchmark \
    && cd /tmp/benchmark \
    && git checkout v1.9.4 \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr \
    && make \
    && make install \
    && rm -rf /tmp/benchmark

RUN apt-get clean && \
    rm -rf /var/lib/apt/lists

# Create working directory with applications
WORKDIR /tmp/workspace

USER user
