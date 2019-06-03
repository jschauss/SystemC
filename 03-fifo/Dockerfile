FROM systemc

COPY . /usr/systemc_projects/fifo

WORKDIR /usr/systemc_projects/fifo/

RUN mkdir build && cd build && \
	export SYSTEMC_BASE=/usr/local/systemc-2.3.2 && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/fifo/build

CMD ["./fifo"]