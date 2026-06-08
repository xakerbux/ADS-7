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
    bool done = false;

    // Выключаем свет в первом вагоне
    current->light = false;

    while (!done) {
        // Идём вперёд на length+1 шагов
        for (int i = 0; i <= length; ++i) {
            current = current->next;
            ++steps;
        }

        if (current->light) {
            // Встретили горящий свет -> выключаем и возвращаемся
            current->light = false;
            for (int i = 0; i <= length; ++i) {
                current = current->prev;
                ++steps;
            }
            ++length;
        } else {
            // Встретили выключенный свет -> включаем и возвращаемся к началу
            current->light = true;
            int backSteps = 0;
            while (current != head) {
                current = current->prev;
                ++steps;
                ++backSteps;
            }
            if (backSteps == length + 1) {
                done = true;
            } else {
                ++length;
            }
        }
    }
    return length + 1;
}

int Train::getOpCount() {
    return steps;
}
