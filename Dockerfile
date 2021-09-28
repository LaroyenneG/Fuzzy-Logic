FROM gcc:9.4

RUN apt-get update
RUN apt-get install -y cmake
RUN apt-get install -y qt5-default

ADD . /opt/fuzzy-logic/
WORKDIR /opt/fuzzy-logic/

RUN cmake CMakeLists.txt
RUN make

RUN mkdir bin

RUN mv titanic ./bin

WORKDIR /opt/fuzzy-logic/bin/

CMD ["./titanic"]
