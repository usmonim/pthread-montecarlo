# pthread-montecarlo
Parallelized Monte Carlo method to estimate π using pthreads and the main thread reads in the total number of tosses and prints the estimate.
I was using ubuntu and gcc compiler to compile the code. 
To compile the code write in terminal: gcc -o  montecarlo_par montecarlo_par.c -lpthread
After it is necassary so that we pass number of threads we want to use in our code. For ex. if we run: ./montecarlo_par 4 then 4 threads is gonna be used to parallelize the code + 1 more threads as the main thread. 
