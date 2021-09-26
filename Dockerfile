FROM gcc:9.4

RUN apt-get update
RUN apt-get install -y cmake
RUN apt-get install -y qt5-default

ADD . /tmp/fuzzy-logic/
WORKDIR /tmp/fuzzy-logic/

RUN cmake CMakeLists.txt
RUN make

RUN cp ./titanic /bin/

WORKDIR /

RUN rm -rf /tmp/fuzzy-logic/

CMD ["titanic"]
