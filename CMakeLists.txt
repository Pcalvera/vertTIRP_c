cmake_minimum_required(VERSION 3.0)
project(vertTIRP_c CUDA)

#find_package(CUDA)
set(CMAKE_CUDA_STANDARD 14)
#set(CMAKE_CUDA_FLAGS "-Wall")

add_executable(vertTIRP_c main.cpp VertTIRP.cpp VertTIRP.h Allen.cpp Allen.h TI.cpp TI.h Allen_relationsEPS.cpp VertTirpSidList.cpp VertTirpSidList.h TIRP.cpp TIRP.h TIRPstatistics.cpp TIRPstatistics.h PairingStrategy.cpp PairingStrategy.h Relation.cpp Relation.h Allen_relationsEPS.h Global.cpp VertTirpNode.cpp VertTirpNode.h Utils.cpp Utils.h Cudaexemple.cu Cudaexemple.cuh)


set_target_properties(vertTIRP_c PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
#target_link_options(vertTIRP_c PRIVATE "/SUBSYSTEM:WINDOWS")