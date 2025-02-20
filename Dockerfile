FROM ubuntu:22.04

RUN apt update && apt install -y build-essential git

RUN apt install -y libasound2-dev libx11-dev \
    libxrandr-dev libxi-dev libgl1-mesa-dev \
    libglu1-mesa-dev libxcursor-dev libxinerama-dev \
    libwayland-dev libxkbcommon-dev wget
    
RUN wget -qO- "https://cmake.org/files/v3.27/cmake-3.27.0-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local && \
    git clone https://github.com/raysan5/raylib.git raylib &&\
    cd raylib &&\
    mkdir build && cd build &&\
    cmake -DBUILD_SHARED_LIBS=ON .. &&\
    make &&\
    make install &&\
    ldconfig


WORKDIR /app
COPY . .

CMD cmake . && make && ./tetris