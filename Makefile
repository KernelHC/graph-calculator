CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS = Vertex.o Edge.o Graph.o CalcMemory.o GCalc.o 
POBJS = Vertex.o Edge.o Graph.o GraphP.o
EXEC = gcalc
DEBUG_FLAG = -g
CXX_COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -fPIC -DNDEBUG
CC_COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
ESSENTIALS = Exceptions.h Vertex.h Vertex.cpp Edge.h Edge.cpp Graph.h Graph.cpp CalcMemory.h CalcMemory.cpp GCalc.cpp graph.i GraphP.h GraphP.cpp


$(EXEC) : $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@
GCalc.o: GCalc.cpp Exceptions.h CalcMemory.h Graph.h Vertex.h Edge.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) GCalc.cpp
libgraph.a: $(POBJS)
	ar -rs libgraph.a $(POBJS)
CalcMemory.o: CalcMemory.cpp CalcMemory.h Graph.h Vertex.h Edge.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) CalcMemory.cpp
Graph.o: Graph.cpp Graph.h Vertex.h Edge.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) Graph.cpp
Edge.o: Edge.cpp Exceptions.h Edge.h Vertex.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) Edge.cpp
Vertex.o: Vertex.cpp Exceptions.h Vertex.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) Vertex.cpp
GraphP.o: GraphP.cpp Graph.h Vertex.h Edge.h GraphP.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(CXX_COMP_FLAG) GraphP.cpp
clean:
	rm -f $(OBJS) $(POBJS) $(EXEC)
tar:
	zip gcalc.zip design.pdf Makefile test_in.txt test_out.txt $(ESSENTIALS)

