#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "define_hariak.h"
#include "tree.h"


struct tree *bst;
/*
 * Core guztietan prozesu gutxien dituenaren identifikadorea lortzeko.
 */
int minimum = 0;
int tam_arr[MAX_CORE_KOP];

int getMincore(int *arr, int kop){
    int i, id, min = 10000000;

    for(i = 0; i < kop; i++){
        if(arr[i] <= min){
            min = arr[i];
            id=i;
        }
    }
    return id;
}

/*
 * Array bat 0 ekin hasieratzeko.
 */
void initArray(int *arr){
    int i;
    for(i = 0; i < MAX_CORE_KOP; i++){
        arr[i] = 0;
    }
}

pthread_mutex_t lock;

/*
 * Schedulerraren funtzioa.
 */
void *scheduler_dispatcher(void *hari_par){

    struct hari_param *param;
    param = (struct hari_param *)hari_par;
    int core_num, i1 = 1, weightval, vrunt, i, sch_tam, min, busy;
    struct process_control_block nulua;
    struct core_t core;
    struct node *lag, *exec;

    //Hasieran sortutako schedulerraren informazioa
    printf("[SCHEDULER/DISPATCHER:    id = %d    name = %s]\n", param->id, param->name);
    sleep(1);
   

    //Hasieraketak
    core_num = param->id - 3;
    busy = 0;

    nulua.pid = -1;
    nulua.weight = -1;
    nulua.vruntime = -1;

    core.core_num = core_num;
    core.root = root;
    sch_tam = sch_arr_tam;
    initArray(tam_arr);

    //Funtzioko loop-ean sartu, mutex baldintzatua erabiliz.
    pthread_mutex_lock(&mutex);
    while(1){
        done++;
        if(i1 == 1){
            i1 = 0;
        }else{
            //pthread_mutex_lock(&lock);
            if(busy == 0 && root->data.pid != -1){
                exec = find_minimum(root);
                printf("---------core%d---------    thread 1: [ id: %d vruntime: %d ]\n", core_num, exec.pid, exec.vruntime);
                root = delete(root, exec->data);
                treetam--;
                busy = 1;
            }else if(root->data.pid == -1){
                exec = root;
                printf("---------core%d---------    thread 1: [ id: %d vruntime: %d ]\n", core_num, exec.pid, exec.vruntime);
            }else{
                printf("---------core%d---------    thread 1: [ id: %d vruntime: %d ]\n", core_num, exec.pid, exec.vruntime);
            }
            vrunt = exec.vruntime;
            vrunt = vrunt - param->timer;
            exec.vruntime = vrunt;

            if(exec.vruntime <= 0){
                busy = 0;
            }
            if(treetam == 0){
                root = new_node(nulua);
                treetam++;
            }
            inorder(root);
            printf("\n");
            //pthread_mutex_unlock(&lock);
        }
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond2, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
