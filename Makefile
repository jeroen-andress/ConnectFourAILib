PYTHON_CONFIG=python3.6-config
CFLAGS=-fPIC -I src
LDFLAGS=-shared `$(PYTHON_CONFIG) --ldflags` -lstdc++
CC=g++
OBJ=ConnectFourAI_wrap.o ConnectFourPlayboard.o ConnectFourPlayerHuman.o ConnectFourPlayerInterface.o ConnectFourPlayerMinimaxAlphaBeta.o ConnectFourPlayerMinimax.o
I=ConnectFourAI.i
SWIG=swig
TARGET=_ConnectFourAI.so
SIDE_PACKAGES_DIR=`python3 -m site --user-site`

all: ConnectFourAI install

ConnectFourAI: $(OBJ) 
	$(CC) -o build/$(TARGET) $(addprefix build/, $(OBJ)) $(LDFLAGS)

install:
	install build/$(TARGET) $(SIDE_PACKAGES_DIR)
	install build/$(subst .i,.py,$(I)) $(SIDE_PACKAGES_DIR)

clean:
	rm -rf build/* 

%_wrap.o: %_wrap.cpp 
	$(CC) $(CFLAGS) `$(PYTHON_CONFIG) --includes` `$(PYTHON_CONFIG) --cflags` -c build/$(subst .o,.cpp,$@) -o build/$@

%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o build/$@

%_wrap.cpp:
	$(SWIG) -o build/$@ -c++ -python src/$(subst _wrap.cpp,.i,$@)
