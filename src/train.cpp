// Copyright 2025 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    do {
        Car* temp = current->next;
        delete current;
        current = temp;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car* wagon = new Car(light);
    if (!first) {
        first = wagon;
        wagon->next = wagon;
        wagon->prev = wagon;
    } else {
        Car* last = first->prev;
        last->next = wagon;
        wagon->prev = last;
        wagon->next = first;
        first->prev = wagon;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* current = first;
    int length = 0;
    bool finished = false;

    current->light = false;

    while (!finished) {
        for (int i = 0; i <= length; ++i) {
            current = current->next;
            ++countOp;
        }

        if (current->light) {
            current->light = false;
            for (int i = 0; i <= length; ++i) {
                current = current->prev;
                ++countOp;
            }
            ++length;
        } else {
            current->light = true;
            int backSteps = 0;
            while (current != first) {
                current = current->prev;
                ++countOp;
                ++backSteps;
            }
            if (backSteps == length + 1) {
                finished = true;
            } else {
                ++length;
            }
        }
    }
    return length + 1;
}

int Train::getOpCount() {
    return countOp;
}
