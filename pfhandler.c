#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct process{
    int pID;
    int VPNumber;
    int useBit;
    process *next;
}process;

typedef struct queue{
    struct process *front;
}queue;

process *pop(queue *myQueue){
    process *temp = myQueue->front;
    myQueue->front = temp->next;
    return temp;
}

void push(queue *myQueue, process *p){
    process *temp = myQueue->front;
    process *prev;
    if(temp == NULL){
        myQueue->front = temp;
    }else{
        while(temp != NULL){
            prev = temp;
            temp = temp->next;
        }
        prev->next = p;
    }
}

process *initProcess(int pID, int VPNumber, int useBit){

    process *p = (process*) malloc(sizeof(process));
    p->pID = pID;
    p->VPNumber = VPNumber;
    p->useBit = useBit;
    return p;
}


int main(){
    char line[10];
    char command[10];
    int numFrames;
    fgets(line,sizeof(line), stdin);
    sscanf(line, "%s", command);
    fgets(line,sizeof(line),stdin);
    sscanf(line, "%d", &numFrames);

    printf("\ncommand:%s, numFrames:%d", command, numFrames);
    //check for local/global
    while(fgets(line, sizeof(line), stdin) != NULL){
        //make call to dependent functions
    }

}