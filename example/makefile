CUDA_INSTALL_PATH= /usr/local/cuda

CC=g++
NVCC=nvcc

CUDA_LIB_HEADER=  ../include/cuvector.h
CUDA_LIB_SOURCES=  ../src/vector/cuvector.cu

CCPFLAGS= -Wno-deprecated-gpu-targets -x cu

main : main.cpp $(CPP_OBJ) $(CUDA_LIB_SOURCES) $(CUDA_LIB_HEADER)
	$(NVCC) $(CCPFLAGS) -o $@ main.cpp $(CPP_OBJ) $(CUDA_LIB_HEADER)

clean:
	@rm *.o main

