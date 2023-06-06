cmake_minimum_required(VERSION 3.18.4)
project(vertTIRP_c)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -fopenmp")

set(CMAKE_CXX_STANDARD 14)
add_executable(vertTIRP_c main.cpp VertTIRP.cpp VertTIRP.h Allen.cpp Allen.h TI.cpp TI.h AllenRelationsEPS.cpp VertTirpSidList.cpp VertTirpSidList.h TIRP.cpp TIRP.h TIRPstatistics.cpp TIRPstatistics.h PairingStrategy.cpp PairingStrategy.h Relation.cpp Relation.h AllenRelationsEPS.h Global.h VertTirpNode.cpp VertTirpNode.h Utils.cpp Utils.h Chrono.cpp Chrono.h)
