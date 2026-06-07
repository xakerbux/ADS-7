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
    int len = 0;
    current->light = false;
    while (true) {
        for (int i = 0; i <= len; ++i) {
            current = current->next;
            ++countOp;
        }
        if (current->light) {
            current->light = false;
            for (int i = 0; i <= len; ++i) {
                current = current->prev;
                ++countOp;
            }
            ++len;
        } else {
            int back = 0;
            while (current != first) {
                current = current->prev;
                ++countOp;
                ++back;
            }
            if (back == len + 1) {
                return len + 1;
            } else {
                current->light = true;
                while (current != first) {
                    current = current->prev;
                    ++countOp;
                }
                ++len;
            }
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
