g++ -c main.cpp VertTIRP.cpp Allen.cpp TI.cpp Utils.cpp Allen_relationsEPS.cpp PairingStrategy.cpp Relation.cpp TIRP.cpp TIRPstatistics.cpp VertTirpSidList.cpp VertTirpNode.cpp
g++ -o executable main.o VertTIRP.o Allen.o TI.o Utils.o Allen_relationsEPS.o PairingStrategy.o Relation.o TIRP.o TIRPstatistics.o VertTirpSidList.o VertTirpNode.o

valgrind --leak-check=yes ./executable