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
    // Выключаем свет в первом вагоне
    current->light = false;
    int len = 1;
    while (true) {
        // Делаем len шагов вперёд
        for (int i = 0; i < len; ++i) {
            current = current->next;
            ++countOp;
        }
        if (current->light) {
            // Встретили включённый свет -> выключаем и возвращаемся
            current->light = false;
            for (int i = 0; i < len; ++i) {
                current = current->prev;
                ++countOp;
            }
            ++len;
        } else {
            // Встретили выключенный свет -> включаем и идём назад до первого
            current->light = true;
            int stepsBack = 0;
            while (current != first) {
                current = current->prev;
                ++countOp;
                ++stepsBack;
            }
            if (stepsBack == len) {
                return len;
            } else {
                // Не первый, продолжаем
                ++len;
            }
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
