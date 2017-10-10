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

bool CPU::ST(int addr, int regNum) {
    this ->ram.write(addr,this->Register[regNum]);
}

bool CPU::LW(int addr, int regNum) {
    this->Register[regNum]=this->ram.read(addr);
}

bool CPU::MOV(int fromReg, int toReg) {
    if(toReg<0||toReg>=16||fromReg<0||fromReg>=16) return false;
    this->Register[toReg] = this->Register[fromReg];
    return true;
}
bool CPU::ADD(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] + this->Register[S2];
}
bool CPU::SUB(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] - this->Register[S2];
}
bool CPU::MUL(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] * this->Register[S2];
}
bool CPU::DIV(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] / this->Register[S2];
}
bool CPU::AND(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] & this->Register[S2];
}
bool CPU::OR(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] | this->Register[S2];
}
bool CPU::MOVI(int val, int toReg){
    this -> Register[toReg] = val;
}
bool CPU::ADDI(int val, int D){
    this->Register[D]+= val;
}
bool CPU::MULI(int val, int D){
    this->Register[D]*= val;
}
bool CPU::DIVI(int val, int D){
    this->Register[D]/= val;
}
bool CPU::LDI(int val, int D){
    this->Register[D]= val;
}
bool CPU::SLT(int S, int B, int D){
    this->Register[D]= (this->Register[S]<this->Register[B])?1:0;
}
bool CPU::SLTI(int S, int val, int D){
    this->Register[D]= (this->Register[S]<val)?1:0;
}
bool CPU::HLT(){
    return true; //end program?
}
bool CPU::NOP(){
    return true;
}
bool CPU::JMP(int lineNo){
    return true; //set lineNo?
}
bool CPU::BEQ(int B, int D, int addr){
    if(this->Register[B]==this->Register[D]) return true; // What is addr?
}
bool CPU::BNE(int B, int D, int addr){
    if(this->Register[B]!=this->Register[D]) return true; // What is addr?
}
bool CPU::BEZ(int B, int addr){
    if(this->Register[B]==0) return true; // What is addr?
}
bool CPU::BNZ(int B, int addr){
    if(this->Register[B]!=0) return true; // What is addr?
}
bool CPU::BGZ(int B, int addr){
    if(this->Register[B]>0) return true; // What is addr?
}
bool CPU::BLZ(int B, int addr){
    if(this->Register[B]<0) return true; // What is addr?
}
//int* CPU::dump_registers() const{
//    return Register;
//}
