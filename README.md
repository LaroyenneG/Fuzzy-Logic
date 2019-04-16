# Fuzzy logic framework

This project exploits the potential of fuzzy logic to allow the titanic to avoid icebergs.

### Project structure :

- _lib/_ : contains cppunit library for testing purposes.
- _assets/_  : contains commons utils files repository.
- _src/_ : contains all sources files.
    - _fuzzylogic/_ : contains the fuzzy logic library. To use the library simply, include _fuzzylogic.h_ file in your project.
    - _leaveATip/_ : contains a short programme using the fuzzy library to help you to be determined the amount of the tip to be paid.
    - _titanic_ : contains a titanic simulator with an automatic pilot using fuzzy logic (automatic iceberg detection).
- test/ : this is the test repository for all sub project.

### Minimum configuration required :

- cmake version 3.13 or more
- g++ GNU compiler
- QT library version 5


#### Commands to build project :

```BATCH
$ git clone https://github.com/LaroyenneG/fuzzy-logic.git
$ cd fuzzy-logic
$ cmake CMakeLists.txt
$ make
```

#### Simulator screenshot
![alt text](./assets/simulator-screen-shot.jpg)
