FROM systemc

COPY . /usr/systemc_projects/motor

WORKDIR /usr/systemc_projects/motor/

RUN mkdir build && cd build && \
	export SYSTEMC_BASE=/usr/local/systemc-2.3.2 && \
	export SYSTEMCAMS_BASE=/usr/local/systemc-ams-2.1 && \
	cmake .. && make
	
WORKDIR /usr/systemc_projects/motor/build

CMD ["./motor"]