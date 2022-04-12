cmake_minimum_required(VERSION 3.21)
project(vertTIRP_c)

set(CMAKE_CXX_STANDARD 14)

add_executable(vertTIRP_c main.cpp VertTIRP.cpp VertTIRP.h Allen.cpp Allen.h TI.cpp TI.h Utils.cpp Allen_relationsEPS.cpp VertTirpSidList.cpp VertTirpSidList.h TIRP.cpp TIRP.h TIRPstatistics.cpp TIRPstatistics.h PairingStrategy.cpp PairingStrategy.h)
