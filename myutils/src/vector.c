#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct vector{
    int *data;
    size_t size;
    size_t capacity;
}vector;

int vector_initialisation(vector* v){
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return 1;
}

int vector_push_back(vector* v, int value){
    if(v->size == v->capacity){
        size_t new_capacity = (v->capacity == 0?4:v->capacity*2);
        if(new_capacity > SIZE_MAX / sizeof(int))return 0;

        int *temp = realloc(v->data, new_capacity*(sizeof(int)));

        if(temp == NULL){
            return 0;
        }
        v->data = temp;
        v->capacity = new_capacity;
    }
    v->data[v->size] = value;
    v->size++;

    return 1;
}


void vector_destory(vector *v){
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return;
}

int main(void){
    vector v;
    vector_initialisation(&v);
    if(!vector_push_back(&v,10) || !vector_push_back(&v,20) || !vector_push_back(&v,30)){
        vector_destory(&v);
        return 1;
    }
    for(size_t i = 0; i < v.size; i++){
        printf("%d ", *(v.data+i));
    }
    printf("\n");
    vector_destory(&v);
    return 0;
}