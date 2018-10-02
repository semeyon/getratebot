# Build container
FROM reo7sp/tgbot-cpp
MAINTAINER Semeyon Svetliy

WORKDIR /tmp

RUN apt-get install -y libspdlog-dev git-core autoconf libtool libjsoncpp-dev libfmt3-dev
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

WORKDIR /usr/getratebot

COPY --from=0 /usr/getratebot/getratebot .

CMD ./getratebot