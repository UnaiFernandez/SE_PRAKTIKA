#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "define_hariak.h"
#include "tree.h"




void *scheduler_dispatcher(void *hari_par){

    struct hari_param *param;
    param = (struct hari_param *)hari_par;
    int core_num, i1 = 1, weightval, vrunt;
    struct process_control_block nulua;
    struct core_t core;
    struct node *root, *exec, *new;

    printf("[SCHEDULER/DISPATCHER:    id = %d    name = %s]\n", param->id, param->name);
    sleep(1);
   
    core_num = param->id - 3;

    nulua.pid = -1;
    nulua.weight = -1;
    nulua.vruntime = -1;

    core.core_num = core_num;
    core.root = root;
    core.tamaina = 0;
    pthread_mutex_lock(&mutex);
    while(1){
        done++;
        if(i1 == 1){
            i1 = 0;
        }else{
            if(atera.pid != 555 && minimum == core_num){
                if(core.tamaina == 0){
                    root = new_node(atera);
                    core.tamaina++;
                }else{
                    insert(root, atera);
                    core.tamaina++;
                }
                tam_arr[core_num] = core.tamaina;
            }
            //printf("[SCHEDULER/DISPATCHER %d] tick read!\n", param->id);
            printf("---------core%d---------     [ %d ]\n", core_num, atera.pid);
            fflush(stdout);
            inorder(root);
            printf("\n");
            sem_post(&sems);
        }
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond2, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
