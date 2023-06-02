g++ -c main.cpp VertTIRP.cpp Allen.cpp TI.cpp Utils.cpp Global.h AllenRelationsEPS.cpp PairingStrategy.cpp Relation.cpp TIRP.cpp TIRPstatistics.cpp VertTirpSidList.cpp VertTirpNode.cpp Chrono.cpp
g++ -o vert_tirp_c -O3 -fopenmp main.o VertTIRP.o Allen.o TI.o Utils.o AllenRelationsEPS.o PairingStrategy.o Relation.o TIRP.o TIRPstatistics.o VertTirpSidList.o VertTirpNode.o Chrono.o

valgrind --leak-check=full --show-leak-kinds=all ./executable