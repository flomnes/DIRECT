CXXFLAGS=-Wall -std=c++11 -lm

CXXFILES=$(wildcard src/*.cpp)
OBJFILES=$(CXXFILES:src/%.cpp=obj/%.o)

all:O2

debug: CXXFLAGS += -DDEBUG -g
debug: direct

O2 : CXXFLAGS += -O2
O2 : direct

direct:${OBJFILES}
	${CXX} ${CXXFLAGS} $^ -o $@

obj/%.o:src/%.cpp
	@[ -d obj ] || mkdir obj
	${CXX} ${CXXFLAGS} $^ -c -o $@

clean:
	@echo "Cleaning..."
	@rm -v obj/*
	@rm -v direct
	@echo "Done."
