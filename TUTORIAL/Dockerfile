FROM ubuntu:latest
LABEL author=CastCris

WORKDIR /TUTORIAL

RUN apt-get update && apt install -y \
build-essential \
libsdl2-dev \
libsdl2-image-dev \
libsdl2-ttf-dev \
libsdl2-mixer-dev \
cmake

COPY ./TUTORIAL .
