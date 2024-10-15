#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]){

    int num_requires = 2;
    if(argc > num_requires + 1){
        printf("arguments given exceed %d. must give exactly %d arguments ",num_requires,num_requires);
        return 0;
    }else if(argc < num_requires + 1){
        printf("arguments given less than %d. must give exactly %d arguments",num_requires,num_requires);
        return 0;
    }

    double start_time, end_time;
    double cpu_time_used;

    start_time = omp_get_wtime(); // start the clocking

    int num_thread = atoi(argv[1]);
    int data_size = atoi(argv[2]);
    int max_value = 99999;
    printf("using %d threads\n",num_thread);
    printf("data size is %d\n",data_size);

    srand(time(NULL)); 
    int i = 0,g = 0,counter = 0,j = 0,count = 0; // private
    int tid; // private
    int* rank = malloc(data_size * sizeof(int));; // shared
    int* SortedArray = malloc(data_size * sizeof(int));// shared
    int* DataArray = malloc(data_size * sizeof(int)); // shared


    if(SortedArray == NULL || DataArray == NULL){
        fprintf(stderr, "Memory allocation failed\n");
    }

    printf("\nData Allocated");
    // printf("\ndata generating..");
    for(i = 0;i < data_size;i++){
        DataArray[i] = rand() % max_value;
        SortedArray[i] = -1; // set as no data
    }
    
    #pragma omp parallel num_threads(num_thread) private(i,j,tid,count)
    {

        tid = omp_get_thread_num();
        #pragma omp for
        for(i = 0;i < data_size;i++){
            count = 0;

            for(j = 0;j < data_size;j++){

                if(DataArray[j] < DataArray[i] || (DataArray[j] == DataArray[i] && j < i)){
                    count++;
                }

            }

            rank[i] = count;

        }

    }

    for(g = 0; g < data_size;g++){
        SortedArray[rank[g]] = DataArray[g];
    }

    end_time = omp_get_wtime(); // end the clocking

    // report time
    cpu_time_used = (end_time - start_time);

    printf("\ntime used %.5f second\n",cpu_time_used);
    printf("\nsorted array (preview 20 elements) : ");

    for(g = 0;g < data_size && g < 20;g++){
        printf(" %d",SortedArray[g]);
    }

    free(DataArray);
    free(SortedArray);
    free(rank);

    

}