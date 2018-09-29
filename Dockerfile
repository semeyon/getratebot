# Build container
FROM reo7sp/tgbot-cpp
MAINTAINER Semeyon Svetliy

WORKDIR /tmp

RUN apt-get install -y libspdlog-dev git-core autoconf libtool
RUN git clone https://github.com/mrtazz/restclient-cpp.git
WORKDIR /tmp/restclient-cpp
RUN ./autogen.sh && \
    ./configure && \
    make install

WORKDIR /usr/getratebot
COPY src src
COPY CMakeLists.txt CMakeLists.txt
RUN cmake . && \
    make -j4


# Run container
FROM reo7sp/tgbot-cpp
MAINTAINER Semeyon Svetliy

ENV TOKEN 641836489:AAEDJMPBDUyCxN0zKD_oAVUMIDD63g1HXnQ

WORKDIR /usr/getratebot

COPY --from=0 /usr/getratebot/getratebot .

CMD ./getratebot