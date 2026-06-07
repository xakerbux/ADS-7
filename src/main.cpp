// Copyright 2025 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "train.h"

int main() {
    std::ofstream data("result/data.csv");
    data << "n,all_off,all_on,random" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int n = 2; n <= 500; n += 10) {
        Train trainOff;
        for (int i = 0; i < n; ++i) {
            trainOff.addCar(false);
        }
        trainOff.getLength();
        int offOps = trainOff.getOpCount();

        Train trainOn;
        for (int i = 0; i < n; ++i) {
            trainOn.addCar(true);
        }
        trainOn.getLength();
        int onOps = trainOn.getOpCount();

        Train trainRand;
        for (int i = 0; i < n; ++i) {
            trainRand.addCar(dis(gen));
        }
        trainRand.getLength();
        int randOps = trainRand.getOpCount();

        data << n << "," << offOps << "," << onOps << "," << randOps << std::endl;
        std::cout << "n=" << n << " done" << std::endl;
    }

    data.close();
    return 0;
}
