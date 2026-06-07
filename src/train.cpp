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
    current->light = false;          // выключаем свет в первом вагоне
    int len = 0;
    while (true) {
        // двигаемся вперёд на len+1 шагов
        for (int i = 0; i <= len; ++i) {
            current = current->next;
            ++countOp;
        }
        if (current->light) {
            // встретили включённый свет — выключаем и возвращаемся
            current->light = false;
            for (int i = 0; i <= len; ++i) {
                current = current->prev;
                ++countOp;
            }
            ++len;
        } else {
            // встретили выключенный — проверяем, не первый ли это вагон
            int steps = 0;
            while (current != first) {
                current = current->prev;
                ++countOp;
                ++steps;
            }
            if (steps == len + 1) {
                // вернулись к первому — нашли длину
                return len + 1;
            } else {
                // это не первый вагон — включаем свет и возвращаемся
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
