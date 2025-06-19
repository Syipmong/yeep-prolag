# Yeep Programming Language v2.0.0 - Docker Image
FROM ubuntu:22.04

# Set metadata
LABEL maintainer="Yipmong Said <syipmong@example.com>"
LABEL description="Yeep Programming Language v2.0.0 - Interactive C++ interpreter"
LABEL version="2.0.0"

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY src/ src/
COPY include/ include/
COPY build_official.sh .
COPY demo_v2.yeep .
COPY README.md .
COPY CHANGELOG.md .

# Build Yeep
RUN chmod +x build_official.sh && \
    ./build_official.sh && \
    cp build/yeep /usr/local/bin/yeep && \
    chmod +x /usr/local/bin/yeep

# Clean up build files to reduce image size
RUN rm -rf build/ src/ include/ build_official.sh

# Create non-root user for security
RUN useradd -m -u 1000 yeep && \
    chown -R yeep:yeep /app

USER yeep

# Set up working directory for user scripts
WORKDIR /workspace

# Default command - start REPL
CMD ["yeep"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD echo 'print("Docker health check");' | yeep || exit 1
