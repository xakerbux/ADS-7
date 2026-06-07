// Copyright 2025 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    Car* nextCar;
    do {
        nextCar = current->next;
        delete current;
        current = nextCar;
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
    bool running = true;
    
    // Выключаем свет в первом вагоне
    if (current->light) {
        current->light = false;
    }
    current = current->next;
    countOp++;
    
    while (running) {
        if (!current->light) {
            current->light = true;
            current = current->prev;
            countOp++;
            if (current == first && current->light) {
                running = false;
            }
        } else {
            current->light = false;
            current = current->next;
            countOp++;
            len++;
        }
    }
    return len;
}

int Train::getOpCount() {
    return countOp;
}
