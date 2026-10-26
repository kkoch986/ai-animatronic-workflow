FROM ubuntu:22.04

# Set working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libopencv-dev \
    libdlib-dev \
    portaudio19-dev \
    libfftw3-dev \
    liblo-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Copy source code
COPY . .

# Create build directory and compile
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Expose port if needed (for OSC communication)
EXPOSE 8000

# Default command
CMD ["./build/animatronic_system"]