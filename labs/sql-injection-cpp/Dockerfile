# ====================================
# Stage 1: Build C++20 Application
# ====================================

FROM debian:bookworm-slim AS builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    libsqlite3-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY CMakeLists.txt .
COPY main.cpp .
COPY Database.h .
COPY Database.cpp .
COPY LessonManager.h .
COPY LessonManager.cpp .
COPY LabManager.h .
COPY LabManager.cpp .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel 2

# ====================================
# Stage 2: Runtime Environment
# ====================================

FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libsqlite3-0 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/bbt_sql_lab /app/bbt_sql_lab

# Copy the SQL Injection Academy website.
COPY web/ /app/web/

RUN useradd --system --no-create-home labuser

USER labuser

EXPOSE 8000

CMD ["/app/bbt_sql_lab"]