FROM ubuntu:latest
LABEL author=CastCris

RUN apt-get update && apt-get install -y \
build-essential \
libsdl2-dev \
libsdl2-image-dev \
libsdl2-ttf-dev \
libsdl2-mixer-dev \
cmake

WORKDIR /SAMPLES
COPY ./SAMPLES .
