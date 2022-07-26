cmake_minimum_required(VERSION 3.7)
project(vertTIRP_c)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCL REQUIRED)

find_package(OpenCL REQUIRED)
add_executable(vertTIRP_c main.cpp VertTIRP.cpp VertTIRP.h Allen.cpp Allen.h TI.cpp TI.h Allen_relationsEPS.cpp VertTirpSidList.cpp VertTirpSidList.h TIRP.cpp TIRP.h TIRPstatistics.cpp TIRPstatistics.h PairingStrategy.cpp PairingStrategy.h Relation.cpp Relation.h Allen_relationsEPS.h Global.h VertTirpNode.cpp VertTirpNode.h Utils.cpp Utils.h)

target_link_libraries(vertTIRP_c OpenCL::OpenCL)