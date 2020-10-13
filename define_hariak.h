/*MAIN PROGRAMAKO DEFINIZIOAK*/
#define HARIKOP 4

struct hari_param{
    int id;
    char * name;
    int p_kop;
    int maiz;
};

void *scheduler_dispatcher(void *hari_param);
void *process_generator(void *hari_param);
void *timer(void *hari_param);
void *clockfunc(void *hari_param);
void sortu_hariak(int hari_kop, int proz_kop, int maiz);

struct process_control_block{
    int pid;
};

// tick en azken balioa irakurtzen dela bermatzeko
extern volatile int tick;
