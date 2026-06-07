// Copyright 2025 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

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
    int result = 0;
    bool flag = false;
    
    while (!flag) {
        if (current->light) {
            current->light = false;
            current = current->next;
            countOp++;
            result++;
        } else {
            current->light = true;
            current = current->prev;
            countOp++;
            if (current == first && current->light) {
                flag = true;
            }
        }
    }
    return result;
}

int Train::getOpCount() {
    return countOp;
}
