FROM systemc

COPY . /usr/src/systemc_projects/alu

WORKDIR /usr/src/systemc_projects/alu/

RUN mkdir build && cd build && \
	export SystemCLanguage=/usr/local/systemc-2.3.1/ && \
	cmake .. && make
	
WORKDIR /usr/src/systemc_projects/alu/build

CMD ["./alu"]