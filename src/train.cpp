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
    // Гарантируем, что в первом вагоне свет выключен
    current->light = false;
    int len = 0;
    bool done = false;
    while (!done) {
        // Делаем len+1 шаг вперёд
        for (int i = 0; i <= len; ++i) {
            current = current->next;
            ++countOp;
        }
        if (current->light) {
            // Встретили включённый свет -> выключаем и возвращаемся
            current->light = false;
            for (int i = 0; i <= len; ++i) {
                current = current->prev;
                ++countOp;
            }
            ++len;
        } else {
            // Встретили выключенный свет -> проверяем, не первый ли это вагон
            int back = 0;
            while (current != first) {
                current = current->prev;
                ++countOp;
                ++back;
            }
            if (back == len + 1) {
                done = true;
            } else {
                // Не первый -> включаем свет и возвращаемся
                current->light = true;
                while (current != first) {
                    current = current->prev;
                    ++countOp;
                }
                ++len;
            }
        }
    }
    return len + 1;
}

int Train::getOpCount() {
    return countOp;
}
