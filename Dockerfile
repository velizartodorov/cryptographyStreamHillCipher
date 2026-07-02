# syntax=docker/dockerfile:1
FROM debian:bookworm-slim AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++ \
        cmake \
        make \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel

# Run the test suite as part of the image build, so a broken build never
# produces a runnable image.
RUN ./build/TestProject

FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
        libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /src/build/StreamHillCipherEncoding /usr/local/bin/
COPY --from=build /src/build/TestProject /usr/local/bin/

CMD ["StreamHillCipherEncoding"]
