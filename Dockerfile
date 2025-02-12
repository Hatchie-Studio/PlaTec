FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update system and install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libpq-dev \
    libssl-dev \
    libreadline-dev \
    zlib1g-dev \
    g++ \
    libpng-dev \
    libgmp3-dev \
    cmake \
    git \
    curl \
    libsass-dev libffi-dev \
    gdb \
    pkg-config && \
    apt-get clean && rm -rf /var/lib/apt/lists/* 


# Set the working directory
WORKDIR /app
COPY . /app

RUN cmake -DWITH_EXAMPLES=TRUE -G "Unix Makefiles"
RUN make