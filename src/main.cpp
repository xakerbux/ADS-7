// Copyright 2025 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "train.h"

int main() {
    std::ofstream file("result/data.csv");
    file << "n,all_off,all_on,random" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int n = 2; n <= 1000; n += 10) {
        // Все лампочки выключены
        Train trainOff;
        for (int i = 0; i < n; ++i) trainOff.addCar(false);
        trainOff.getLength();
        int offSteps = trainOff.getOpCount();

        // Все лампочки включены
        Train trainOn;
        for (int i = 0; i < n; ++i) trainOn.addCar(true);
        trainOn.getLength();
        int onSteps = trainOn.getOpCount();

        // Случайное распределение
        Train trainRand;
        for (int i = 0; i < n; ++i) trainRand.addCar(dis(gen));
        trainRand.getLength();
        int randSteps = trainRand.getOpCount();

        file << n << "," << offSteps << "," << onSteps << "," << randSteps
             << std::endl;
        std::cout << "n=" << n << " done" << std::endl;
    }

    file.close();
    return 0;
}
