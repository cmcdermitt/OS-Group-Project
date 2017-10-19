//
// Created by Eshin Griffith on 9/26/17.
//

#include "CPU.h"
#include "Utility.h"


bool CPU::Operate() {
    std::string instruction = CPU::fetch(this->PC);
    ++PC;
    Op decoded = CPU::decode(instruction);
    CPU::execute(decoded);
}

CPU::CPU(RAM* ram,mode m) {
    this -> cpumode = m;
    if(m==debug) std::cout<<"--DEBUG--\n";
    this->ram = ram;
    for (int i = 0; i < 16; ++i) {
        this->Register[i]=i;
    }
    this->Register[1] = 0;
}

bool CPU::RD(int s1, int s2, int address) {

    if(this->cpumode==debug) return false;
    if(address==0)Register[s1] = Utility::convertHexToDecimal(ram->read(Register[s2]/4));
    else Register[s1] = Utility::convertHexToDecimal(ram->read((address)/4));

}

bool CPU::WR(int s1, int s2, int address) {
    if(this->cpumode==debug) return false;
    ram->write(address/4,Utility::convert_decimal_to_hex(Register[s1]));

}

bool CPU::ST(int addr, int breg, int dreg) {
//    this ->ram.write(addr,this->Register[regNum]);
    //Utility::convert_decimal_to_hex
    if(addr==0) ram->write(Register[dreg]/4, Utility::convert_decimal_to_hex(Register[breg]));
    else ram->write(addr/4, Utility::convert_decimal_to_hex(Register[breg]));
    return true;
}

bool CPU::LW(int addr, int breg, int dreg) {
    if(addr==0)this->Register[dreg] = Utility::convertHexToDecimal(this->ram->read(Register[breg]/4));
    else this->Register[dreg] = Utility::convertHexToDecimal(this->ram->read(addr/4));
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
bool CPU::MOVI(int val, int D){
    this -> Register[D] = val;
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
    PC = lineNo/4;
    return true;
}
bool CPU::BEQ(int B, int D, int addr){
    if(this->Register[B]==this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BNE(int B, int D, int addr){
    if(this->Register[B]!=this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BEZ(int B, int addr){
    if(this->Register[B]==0) JMP(addr);
    return true;
}
bool CPU::BNZ(int B, int addr){
    if(this->Register[B]!=0) JMP(addr);
    return true;
}
bool CPU::BGZ(int B, int addr){
    if(this->Register[B]>0) JMP(addr);
    return true;
}
bool CPU::BLZ(int B, int addr){
    if(this->Register[B]<0) JMP(addr);
    return true;
}

int *CPU::dump_registers() {
    return Register;
}

std::string CPU::fetch(int i) {
    return this->ram->read(i+state.job_ram_address);
}

Op CPU::decode(std::string hex) {
    std::string instruction = Utility::HexToBinary(hex);
    Op inst;
    inst.opType = instruction.substr(0,2);
    inst.opCode = Utility::BinaryToHex(instruction.substr(2,6));
    if(inst.opType=="00"){
        inst.sReg1 = Utility::convertBinaryToDecimal(instruction.substr(8 ,4));
        inst.sReg2 = Utility::convertBinaryToDecimal(instruction.substr(12,4));
        inst.dReg  = Utility::convertBinaryToDecimal(instruction.substr(16,4));
        inst.address = -1;
        inst.bReg = -1;

    }
    else if(inst.opType=="01"){
        inst.bReg = Utility::convertBinaryToDecimal(instruction.substr(8 ,4));
        inst.dReg = Utility::convertBinaryToDecimal(instruction.substr(12,4));
        inst.address = Utility::convertBinaryToDecimal(instruction.substr(16,16));
        inst.sReg1 = -1;
        inst.sReg2 = -1;
    }
    else if(inst.opType=="10"){
        inst.address = Utility::convertBinaryToDecimal(instruction.substr(8,24));
        inst.sReg1 = -1;
        inst.sReg2 = -1;
        inst.bReg = -1;
        inst.dReg = -1;

    }
    else if(inst.opType=="11"){
        inst.sReg1 = Utility::convertBinaryToDecimal(instruction.substr(8 ,4));
        inst.sReg2 = Utility::convertBinaryToDecimal(instruction.substr(12,4));
        inst.address  = Utility::convertBinaryToDecimal(instruction.substr(16,16));
        inst.bReg = -1;
        inst.dReg = -1;
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
        else if(op.opCode=="10")CPU::SLT(op.sReg1,op.sReg2,op.dReg);
        else if(op.opCode=="0A")CPU::OR(op.sReg1,op.sReg2,op.dReg);
    }else
    if(op.opType=="01"){
             if(op.opCode=="02")CPU::ST(op.address,op.bReg,op.dReg);
        else if(op.opCode=="03")CPU::LW(op.address,op.bReg,op.dReg);
        else if(op.opCode=="0B")CPU::MOVI(op.address,op.dReg);
        else if(op.opCode=="0C")CPU::ADDI(op.address,op.dReg);
        else if(op.opCode=="0D")CPU::MULI(op.address,op.dReg);
        else if(op.opCode=="0E")CPU::DIVI(op.address,op.dReg);
        else if(op.opCode=="0F")CPU::LDI(op.address,op.dReg);
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
             if(op.opCode=="00")CPU::RD(op.sReg1,op.sReg2,op.address);
        else if(op.opCode=="01")CPU::WR(op.sReg1,op.sReg2,op.address);
    }
}

void CPU::loadPCB(PCB *p) {
    this->state = *p;
    PC = p->prgm_counter;
    this->state.state = PCB::RUNNING;
    for (int i = 0; i < 16; ++i) {
        this->Register[i] = this->state.registers[i];
    }
}
PCB* CPU::storePCB() {
    PCB* out = &state;
    if(this->state.state != PCB::COMPLETED) this->state.state = PCB::READY;
    out->prgm_counter = PC;
    for (int i = 0; i < 16; ++i) {
        this->state.registers[i] = this->Register[i];
    }
    return out;
}
void CPU::pass(std::string val){
    Op decoded = CPU::decode(val);
    std::cout << "OpType: " << decoded.opType << std::endl;
    std::cout << "OpCode: " << decoded.opCode << std::endl;
    std::cout << "sReg1: " << decoded.sReg1 << std::endl;
    std::cout << "sReg2: " << decoded.sReg2 << std::endl;
    std::cout << "dReg: " << decoded.dReg << std::endl;
    std::cout << "bReg: " << decoded.bReg << std::endl;
    std::cout << "address: " << decoded.address << std::endl <<std::endl;


    CPU::execute(decoded);
    for(int i=0;i<16;i++){
        std::cout << i <<"\t";
    }
    std::cout << std::endl;
    for (int i : this->Register) {
        std::cout << i <<"\t";
    }
    std::cout << std::endl;
}
void CPU::test(){
    CPU cpu = CPU(new RAM(),debug);
    cpu.pass("C050005C");
    cpu.pass("4B060000");
    cpu.pass("4B0A0000");
    cpu.pass("4C0A0004");
}