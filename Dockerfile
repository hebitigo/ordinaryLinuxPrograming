FROM ubuntu:latest

RUN mkdir /workspace

WORKDIR /workspace

RUN apt-get update \
    && apt-get install -y build-essential \
    && apt-get install -y man \
    && apt-get install -y vim 