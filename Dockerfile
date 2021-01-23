From rushmash/gcc-arm-embedded-docker:latest
RUN git clone --depth 1 -b v1.8.0 https://github.com/STMicroelectronics/STM32CubeH7.git /opt/STM32CubeH7 \
    && rm -fr /opt/STM32CubeH7/Projects/ \
    && rm -fr /opt/STM32CubeH7/.git/

WORKDIR /usr/src/app
ENTRYPOINT cmake -GNinja -Bbuild . \
    && ninja -Cbuild \
    && chmod -R 777 build
