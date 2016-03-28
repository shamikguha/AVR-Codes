We will be using avr gcc compiler to build and execute the code. 

The code initially changes the CPU frequency to 8Mhz as asked. But it is to be noted that without appropriate change in the fuse bits, this might not work properly.

The function initSquareWave is written for generating the 2Khz frequency square wave.

The required registers have been invoked and used appropriately.

The working is described in the comments mentioned in the code Question_5.c