CC=nvcc
CUDA_CC=nvcc
CPP_SOURCES= 
CUDA_SOURCES= matrix.cu

CPP_OBJ= $(CPP_SOURCES:.cpp=.o)
CPP_HEADERS= $(CPP_SOURCES:.cpp=.h)

CUDA_HEADERS= $(CUDA_SOURCES:.cu=.h)
CUDA_OBJ= $(CUDA_SOURCES:.cu=.o)

CCPFLAGS= 
CUDAFLAGS= -Wno-deprecated-gpu-targets

main : main.cpp $(CUDA_OBJ) $(CPP_OBJ)
	@$(CUDA_CC) $(CUDAFLAGS) -o $@ $+

%.o : %.cu %.h
	@$(CUDA_CC) $(CUDAFLAGS) -c -o $@ $<

%.o : %.cpp %.h
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm *.o main

