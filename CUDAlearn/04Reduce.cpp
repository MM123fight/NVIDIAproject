#include <stdio.h>

//See the course from 127 video
#define NUM_BLOCKS 1024
#define BLOCK_WIDTH 1024

__global__ void shmem_reduce_kernel(float *d_out, const float *d_in){

    // sdata is allocated in the kernel call: 3rd arg to <<<blocknum,threadnum,shmem>>>
    extern __shared__ float sdata[];

    int myId = threadIdx.x + blockDim.x * blockIdx.x;
    int tid = threadIdx.x;

    // load shared memory from global memory
    sdata[tid] = d_in[myId];
    __syncthreads();  // make sure entire block is loaded

    // do reduction in shared memory
    for(unsigned int s = blockDim.x/2; s >0; s >>= 1){
        if(tid < s){
            sdata[tid] += sdata[tid+s];
        }
        __syncthreads();
    }
    if(tid == 0){
        d_out[blockIdx.x] = sdata[0];
    }
}

