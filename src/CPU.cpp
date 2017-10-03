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

bool CPU::MOV(int fromReg, int toReg) {
    if(toReg<0||toReg>=16||fromReg<0||fromReg>=16) return false;
    this->Register[toReg] = this->Register[fromReg];
    return true;
}

int* CPU::dump_registers() const{
    return Register;
}
