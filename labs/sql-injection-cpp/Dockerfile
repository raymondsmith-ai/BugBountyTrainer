FROM debian:bookworm-slim AS builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY CMakeLists.txt .
COPY main.cpp .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel 2

FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /app/build/bbt_sql_lab /app/bbt_sql_lab

RUN useradd --system --no-create-home labuser

USER labuser

EXPOSE 8000

CMD ["/app/bbt_sql_lab"]