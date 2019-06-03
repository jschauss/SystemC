FROM systemc

COPY . /usr/systemc_projects/fifo

WORKDIR /usr/systemc_projects/fifo/

RUN mkdir build && cd build && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/fifo/build

CMD ["./fifo"]