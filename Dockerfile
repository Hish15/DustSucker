From rushmash/gcc-arm-embedded-docker:latest
RUN git clone --depth 1 -b v1.8.0 https://github.com/STMicroelectronics/STM32CubeH7.git /opt/STM32CubeH7
WORKDIR /home/
ENTRYPOINT cmake -GNinja -Bbuild . && ninja -Cbuild
