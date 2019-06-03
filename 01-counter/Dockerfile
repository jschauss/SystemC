FROM systemc

COPY . /usr/systemc_projects/counter

WORKDIR /usr/systemc_projects/counter/

RUN mkdir build && cd build && \
	export SYSTEMC_BASE=/usr/local/systemc-2.3.2 && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/counter/build

CMD ["./counter"]