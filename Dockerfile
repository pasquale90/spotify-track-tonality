FROM debian:12

WORKDIR /home/eyeharp/spotify-track-tonality

RUN apt-get update -y \ 
    && apt-get install -y \
    wget \
    nano \ 
    build-essential \
    cmake \
    git \
    libcurl4-openssl-dev \ 
    nlohmann-json3-dev \ 
    libjsoncpp-dev

    
# install spotifeye
RUN cd ${WORKDIR}
RUN mkdir ./src
RUN mkdir ./include 
RUN mkdir ./spotify
COPY src ./src
COPY include ./include
COPY CMakeLists.txt .
COPY spotify/credentials.json ./spotify/credentials.json
#build spotifeye
RUN mkdir build && cd build && cmake ../ && cmake --build .