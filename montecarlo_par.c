#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;

long long int number_of_tosses;

int num_threads;

int thread;
/////////////////////////////////////////////////////////////// 
// int number_in_circle = 0;
/////////////////////////////////////////////////////////////////
int number_in_circle_final;

double pi_estimate;

void* estimates(void* rank);

double rand_range(double min, double max);

int main(int argc, char* argv[]){
    printf("Enter Total #of tosses: \n");
    scanf("%lld", &number_of_tosses);

    long thread;  
   	pthread_t* thread_handles;
    num_threads = strtol(argv[1], NULL, 10);
   	thread_handles = malloc (num_threads*sizeof(pthread_t));

    pthread_mutex_init(&mutex, NULL);

    for (thread = 0; thread < num_threads; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          estimates, (void*)thread);

    for (thread = 0; thread < num_threads; thread++) 
      pthread_join(thread_handles[thread], NULL);      
    
    // printf("%lld \n", number_of_tosses);
    // printf("%d \n", num_threads);

    // double result = estimates();
    // printf ( "%f\n", result);

    // estimates();
    pi_estimate = 4 * number_in_circle_final / ((double) number_of_tosses);
    printf("pi = %f \n", pi_estimate);

    double estimate = number_in_circle_final / (double) number_of_tosses;
    printf("Estimate = %f \n", estimate);

    pthread_mutex_destroy(&mutex);

    free(thread_handles);
    return 0;
}

void* estimates(void* rank){
    long my_rank = (long) rank;
    long long my_n = number_of_tosses/num_threads;
    long long my_first_toss = my_n*my_rank;
    long long my_last_toss = my_first_toss + my_n;
//////////////////////////////////////////////////////////////////////////
    int number_in_circle = 0;
////////////////////////////////////////////////////////////////////////////     
    
    srand ( time (0));

    for (int toss = my_first_toss; toss < my_last_toss; toss++) {
        double x = rand_range(-1.0, 1.0);
        // printf("x = %f \n", x);
        double y = rand_range(-1.0, 1.0);
        // printf("y = %f \n", y);
        double distance_squared = x*x + y*y;
        // printf("distance_squared = %f \n", distance_squared);
        if(distance_squared <= 1){
//////////////////////////////////////////////////////////////////////////////////////////            
            // pthread_mutex_lock(&mutex);
            number_in_circle++;
            // pthread_mutex_unlock(&mutex);
//////////////////////////////////////////////////////////////////////////////////////////////            

        }
    }

    pthread_mutex_lock(&mutex);
    number_in_circle_final += number_in_circle;
    pthread_mutex_unlock(&mutex);
    printf("Num of Circle = %d \n", number_in_circle_final);

    // pi_estimate = 4 * number_in_circle / ((double) number_of_tosses);
    // printf("pi_estimate = %f \n", pi_estimate);

    return NULL;
        
}
// random double generator
double rand_range(double min, double max){
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

