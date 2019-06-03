FROM systemc

COPY . /usr/systemc_projects/alu

WORKDIR /usr/systemc_projects/alu/

RUN mkdir build && cd build && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/alu/build

CMD ["./alu"]