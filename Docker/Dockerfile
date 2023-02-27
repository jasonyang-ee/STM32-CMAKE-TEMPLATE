FROM ubuntu:22.04

ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
ARG ARM_VERSION=12.2.rel1

# Prep basic packages
RUN apt update && apt-get clean && apt-get install -y \
	build-essential \
	cmake ninja-build \
	git \
	stlink-tools \
	xz-utils curl

# Get ARM Toolchain
RUN mkdir ${TOOLS_PATH} \
	&& curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-x86_64-arm-none-eabi.tar.xz" \
	&& tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH}

# Clean Up
RUN rm gcc-arm-none-eabi.tar.xz \
	&& rm ${TOOLS_PATH}/*.txt \
	&& rm -rf ${TOOLS_PATH}/share/doc \
	&& apt remove -y xz-utils curl

# Add Toolchain to PATH
ENV PATH="$PATH:${TOOLS_PATH}/bin"

ADD build.sh /usr/local/bin/build.sh
ENTRYPOINT ["/bin/bash", "build.sh"]
