FROM gcc:7.3.0

RUN apt-get -qq update
RUN apt-get -qq upgrade

RUN apt-get -qq install build-essential wget && cd ~ && \
	wget http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.2.tar.gz && \
	tar -xzf systemc-2.3.2.tar.gz && cd systemc-2.3.2 && mkdir objdir && cd objdir && \
	mkdir /usr/local/systemc-2.3.2 && ../configure --prefix=/usr/local/systemc-2.3.2/ && \
	make && make install

RUN apt-get -qq install cmake