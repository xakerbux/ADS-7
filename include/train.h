// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 public:
    Train();
    ~Train();
    void addCar(bool light);
    int getLength();
    int getOpCount();

 private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;
        explicit Car(bool l) : light(l), next(nullptr), prev(nullptr) {}
    };
    Car* first;
    int countOp;
};

#endif  // INCLUDE_TRAIN_H_
