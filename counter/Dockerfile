FROM systemc

COPY . /usr/systemc_projects/counter

WORKDIR /usr/systemc_projects/counter/

RUN mkdir build && cd build && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/counter/build

CMD ["./counter"]