FROM alpine:3.6
RUN apk update
RUN apk add gcc g++ make git gnutls-dev gnutls-c++ clang
RUN echo "To run the program type : \"cd code && ./maze \" then choose the maze you want to solve : r1.txt, r2.txt, r3.txt, r4.txt, r5.txt, o1.txt "
