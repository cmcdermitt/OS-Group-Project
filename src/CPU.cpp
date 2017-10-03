//
// Created by Eshin Griffith on 9/26/17.
//

#include "CPU.h"

bool CPU::Operate(int code) {
    return false;
}

CPU::CPU(RAM ram) {
    this->ram = ram;
}

bool CPU::RD() {
    return false;
}

bool CPU::WR() {
    return false;
}

bool CPU::ST(int regNum) {
    return false;
}

bool CPU::LW(int addr, int regNum) {
    return false;
}
