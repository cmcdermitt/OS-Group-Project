//
// Created by Eshin Griffith on 9/26/17.
//

#include "CPU.h"
#include "Utility.h"


bool CPU::Operate() {
    std::string instruction = CPU::fetch(this->Register[0]);
    Register[0]++;
    Op decoded = CPU::decode(instruction);
    CPU::execute(decoded);
}

CPU::CPU(RAM* ram) {
    this->ram = ram;
    this->Register[1]=0;
}

bool CPU::RD() {
    return false;
}

bool CPU::WR() {
    return false;
}

bool CPU::ST(int addr, int regNum) {
//    this ->ram.write(addr,this->Register[regNum]);
    //Utility::convert_decimal_to_hex
    return true;
}

bool CPU::LW(int addr, int regNum) {
    this->Register[regNum] = Utility::convertHexToDecimal(this->ram->read(addr));
    return true;
}

bool CPU::MOV(int fromReg, int toReg) {
    if(toReg<0||toReg>=16||fromReg<0||fromReg>=16) return false;
    this->Register[toReg] = this->Register[fromReg];
    return true;
}
bool CPU::ADD(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] + this->Register[S2];
    return true;
}
bool CPU::SUB(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] - this->Register[S2];
    return true;
}
bool CPU::MUL(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] * this->Register[S2];
    return true;
}
bool CPU::DIV(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] / this->Register[S2];
    return true;
}
bool CPU::AND(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] & this->Register[S2];
    return true;
}
bool CPU::OR(int S1, int S2, int D){
    this->Register[D] = this->Register[S1] | this->Register[S2];
    return true;
}
bool CPU::MOVI(int val, int toReg){
    this -> Register[toReg] = val;
    return true;
}
bool CPU::ADDI(int val, int D){
    this->Register[D]+= val;
    return true;
}
bool CPU::MULI(int val, int D){
    this->Register[D]*= val;
    return true;
}
bool CPU::DIVI(int val, int D){
    this->Register[D]/= val;
    return true;
}
bool CPU::LDI(int val, int D){
    this->Register[D]= val;
    return true;
}
bool CPU::SLT(int S, int B, int D){
    this->Register[D]= (this->Register[S]<this->Register[B])?1:0;
    return true;
}
bool CPU::SLTI(int S, int val, int D){
    this->Register[D]= (this->Register[S]<val)?1:0;
    return true;
}
bool CPU::HLT(){
    this->state.state = state.COMPLETED;
    return true; //end program?
}
bool CPU::NOP(){
    return true;
}
bool CPU::JMP(int lineNo){
    Register[0] = lineNo;
    return true;
}
bool CPU::BEQ(int B, int D, int addr){
    if(this->Register[B]==this->Register[D]) return true; // What is addr?
    return true;
}
bool CPU::BNE(int B, int D, int addr){
    if(this->Register[B]!=this->Register[D]) return true; // What is addr?
    return true;
}
bool CPU::BEZ(int B, int addr){
    if(this->Register[B]==0) return true; // What is addr?
    return true;
}
bool CPU::BNZ(int B, int addr){
    if(this->Register[B]!=0) return true; // What is addr?
    return true;
}
bool CPU::BGZ(int B, int addr){
    if(this->Register[B]>0) return true; // What is addr?
    return true;
}
bool CPU::BLZ(int B, int addr){
    if(this->Register[B]<0) return true; // What is addr?
    return true;
}

int *CPU::dump_registers() {
    return Register;
}

std::string CPU::fetch(int i) {
    return this->ram->read(i+state.job_ram_address);
}

Op CPU::decode(std::string instruction) {
    std::string binInstruction = Utility::HexToBinary(instruction);
    Op inst;
    inst.opType = instruction.substr(2);
    inst.opCode = Utility::BinaryToHex(instruction.substr(2,8));
    if(inst.opType=="00"){
        inst.sReg1 = Utility::convertBinaryToDecimal(instruction.substr(8 ,12));
        inst.sReg2 = Utility::convertBinaryToDecimal(instruction.substr(12,16));
        inst.dReg  = Utility::convertBinaryToDecimal(instruction.substr(16,20));
    }
    else if(inst.opType=="01"){
        inst.bReg = Utility::convertBinaryToDecimal(instruction.substr(8 ,12));
        inst.dReg = Utility::convertBinaryToDecimal(instruction.substr(12,16));
        inst.address = Utility::convertBinaryToDecimal(instruction.substr(16,32));
    }
    else if(inst.opType=="10"){
        inst.address = Utility::convertBinaryToDecimal(instruction.substr(8,32));
    }
    else if(inst.opType=="11"){
        inst.sReg1 = Utility::convertBinaryToDecimal(instruction.substr(8 ,12));
        inst.sReg2 = Utility::convertBinaryToDecimal(instruction.substr(12,16));
        inst.address  = Utility::convertBinaryToDecimal(instruction.substr(16,32));
    }
    return inst;
}

void CPU::execute(Op op) {
    if(op.opType=="00"){
             if(op.opCode=="04")CPU::MOV(op.sReg1,op.sReg2);
        else if(op.opCode=="05")CPU::ADD(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="06")CPU::SUB(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="07")CPU::MUL(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="08")CPU::DIV(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="09")CPU::AND(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="0A")CPU::OR(op.sReg1,op.sReg2,op.dReg);
    }else
    if(op.opType=="01"){
        if(op.dReg!=0){
            op.address = op.address + op.dReg;
        }
             if(op.opCode=="02")CPU::ST(op.address,op.bReg);
        else if(op.opCode=="03")CPU::LW(op.address,op.bReg);
        else if(op.opCode=="0B")CPU::MOVI(op.address,op.bReg);
        else if(op.opCode=="0C")CPU::ADDI(op.address,op.bReg);
        else if(op.opCode=="0D")CPU::MULI(op.address,op.bReg);
        else if(op.opCode=="0E")CPU::DIVI(op.address,op.bReg);
        else if(op.opCode=="0F")CPU::LDI(op.address,op.bReg);
        else if(op.opCode=="11")CPU::SLTI(op.bReg,op.address,op.dReg);
        else if(op.opCode=="15")CPU::BEQ(op.bReg,op.dReg,op.address);
        else if(op.opCode=="16")CPU::BNE(op.bReg,op.dReg,op.address);
        else if(op.opCode=="17")CPU::BEZ(op.bReg,op.address);
        else if(op.opCode=="18")CPU::BNZ(op.bReg,op.address);
        else if(op.opCode=="19")CPU::BGZ(op.bReg,op.address);
        else if(op.opCode=="1A")CPU::BLZ(op.bReg,op.address);
    }else
    if(op.opType=="10"){
             if(op.opCode=="12")CPU::HLT();
        else if(op.opCode=="14")CPU::JMP(op.address);
    }else
    if(op.opType=="11"){
             if(op.opCode=="00")CPU::RD();
        else if(op.opCode=="01")CPU::WR();
    }
}

void CPU::loadPCB(PCB p) {
    this->state = p;
    for (int i = 0; i < 16; ++i) {
        this->Register[i] = this->state.registers[i];
    }
}
PCB CPU::storePCB() {
    for (int i = 0; i < 16; ++i) {
        this->state.registers[i] = this->Register[i];
    }
    return state;
}

//void CPU::test(){
//    CPU cpu = CPU(RAM());
////    cpu.Register = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};
//}