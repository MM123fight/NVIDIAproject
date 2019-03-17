#include <stdio.h>

//See the course from 87 video
#define NUM_BLOCKS 1
#define BLOCK_WIDTH 128

__global__ void shiftleft(){
    int idx = threadIdx.x;
    __shared__ int array[BLOCK_WIDTH];
    array[idx] = threadIdx.x;
    __syncthreads();
    if(idx < BLOCK_WIDTH-1){
        int temp = array[idx+1];
        __syncthreads();
        array[idx] = temp;
        __syncthreads();
    }
}

__global__ void tripleaverage(){
    int idx = threadIdx.x;
    __shared__ float array[BLOCK_WIDTH];
    array[idx] = float(threadIdx.x);
    __syncthreads();
    if((idx < BLOCK_WIDTH - 1)&&(idx > 1)){
        float temp = (array[idx-1] + array[idx] + array[idx+1])/3.0;
        __syncthreads();
        array[idx] = temp;
        __syncthreads();
    }

}
int main(int argc, char **argv){

    shiftleft<<<NUM_BLOCKS,BLOCK_WIDTH>>>();
    return 0;
}

