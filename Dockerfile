FROM gcc:7.3.0

RUN apt-get -qq update
RUN apt-get -qq upgrade

RUN apt-get -qq install build-essential wget && cd ~ && \
	wget http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.2.tar.gz && \
	tar -xzf systemc-2.3.2.tar.gz && cd systemc-2.3.2 && mkdir objdir && cd objdir && \
	mkdir /usr/local/systemc-2.3.2 && ../configure --prefix=/usr/local/systemc-2.3.2/ && \
	make && make install
	
COPY ./systemc_ams/systemc-ams-2.1.tar.gz . 

RUN tar -xzf systemc-ams-2.1.tar.gz && cd systemc-ams-2.1 && \
	mkdir objdir && cd objdir && mkdir /usr/local/systemc-ams-2.1 && \
	../configure --prefix=/usr/local/systemc-ams-2.1/ --with-systemc=/usr/local/systemc-2.3.2 && \
	sed -i '41i\''\n#include <cstring>\n' /systemc-ams-2.1/src/scams/impl/predefined_moc/tdf/sca_tdf_ct_vector_ss_proxy.h && \
	sed -i '41i\''\n#include <cstring>\n' /systemc-ams-2.1/src/scams/impl/predefined_moc/tdf/sca_tdf_ct_ltf_nd_proxy.h && \
	make && make install

RUN apt-get -qq install cmake