FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    g++ \
    libgtest-dev \
    make \
    curl \
    doxygen \
    vim

WORKDIR /app

COPY . /app

CMD ["make"]