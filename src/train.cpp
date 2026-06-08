// Copyright 2025 NNTU-CS
#include "train.h"

Train::Train() : steps(0), head(nullptr) {}

Train::~Train() {
    if (!head) return;
    Car* current = head;
    do {
        Car* nextCar = current->next;
        delete current;
        current = nextCar;
    } while (current != head);
}

void Train::addCar(bool light) {
    Car* newCar = new Car(light);
    if (!head) {
        head = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = head->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = head;
        head->prev = newCar;
    }
}

int Train::getLength() {
    if (!head) return 0;
    steps = 0;
    Car* current = head;
    int length = 0;
    bool finished = false;

    while (!finished) {
        if (current->light) {
            current->light = false;
            current = current->next;
            ++steps;
            ++length;
        } else {
            current->light = true;
            current = current->prev;
            ++steps;
            if (current == head && current->light) {
                finished = true;
            }
        }
    }
    return length;
}

int Train::getOpCount() {
    return steps;
}
