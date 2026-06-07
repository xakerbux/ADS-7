// Copyright 2025 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    do {
        Car* next = current->next;
        delete current;
        current = next;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car* newCar = new Car(light);
    if (!first) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* current = first;
    int len = 1;
    bool done = false;
    
    while (!done) {
        // Идём вперёд на len шагов
        for (int i = 0; i < len; ++i) {
            current = current->next;
            countOp++;
        }
        
        if (current->light) {
            // Включён -> выключаем и возвращаемся
            current->light = false;
            for (int i = 0; i < len; ++i) {
                current = current->prev;
                countOp++;
            }
            len++;
        } else {
            // Выключён -> включаем и идём назад до первого
            current->light = true;
            int steps = 0;
            while (current != first) {
                current = current->prev;
                countOp++;
                steps++;
            }
            if (steps == len) {
                done = true;
            } else {
                len++;
            }
        }
    }
    return len;
}

int Train::getOpCount() {
    return countOp;
}
