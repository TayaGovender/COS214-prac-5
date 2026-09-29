FROM ubuntu:24.04

WORKDIR /app

RUN apt-get update && apt-get install -y g++ make valgrind gdb

COPY . .

RUN make clean && make

CMD ["./campusguard_test"]