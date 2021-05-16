#include "queue.h"

queue_t *create_queue(int capacity){
    queue_t *queue = malloc(sizeof(queue_t));
    if(!queue){
        return NULL;
    }
    queue->head = queue->tail = 0;
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = malloc(sizeof(void*) * (queue->capacity));
    return queue;
}

bool push_to_queue(queue_t *queue, void *data) {
   if(queue->size >= queue->capacity){
      return false;
   }
   
   queue->size++;
   queue->array[(queue->tail++)%queue->capacity] = data;
   return true;
}

void* pop_from_queue(queue_t *queue){
    if(queue->head == queue->tail && queue->size == 0){
        return NULL;
    }
    queue->size--;
    return queue->array[(queue->head++)%queue->capacity]; 
}

void clean_queue(queue_t *queue){
    for(int i = queue->head; i < queue->tail; i++){
    
        void * popped = pop_from_queue(queue);
        if(popped != NULL){
            free(popped);
        }
    }
}

void* get_from_queue(queue_t *queue, int idx){
    return queue->array[(idx)%queue->capacity];
}

void delete_queue(queue_t *queue){
    clean_queue(queue);
    free(queue->array);
    queue->size = queue->head = queue->tail = 0;
    free(queue);
}

int get_queue_size(queue_t *queue){
    return abs((queue->tail) - (queue->head));
}
