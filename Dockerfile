FROM ubuntu:20.04

# Avoid timezone prompt
ENV DEBIAN_FRONTEND=noninteractive 

# Install essential software
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    mesa-utils \
    libgl1-mesa-dri \
    libgl1-mesa-glx \
    libglfw3-dev \
    libglew-dev \
    libassimp-dev \
    freeglut3-dev \
    xorg-dev \
    x11-apps && \
    apt-get clean

# Set environment for software rendering
ENV LIBGL_ALWAYS_SOFTWARE=1

WORKDIR /app

COPY . .

# Build your OpenGL project
RUN mkdir build && cd build && \
    cmake .. && \
    make

CMD ["./build/terrarian-render"]

