FROM alpine:3.6
WORKDIR /app
COPY . .
RUN apk update
RUN apk add gcc
RUN apk add musl-dev
RUN gcc -o maze ./code/dfs.c
RUN echo "Executing last maze with DFS algorithm"
RUN ./maze ./code/r5.txt