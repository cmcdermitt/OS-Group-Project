//
// Created by Eshin Griffith on 9/26/17.
//

#include "CPU.h"
#include "Utility.h"
#include "Log.h"


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
    has_been_used = false;
}

bool CPU::get_has_been_used() { return has_been_used;}
bool CPU::set_to_used() {has_been_used = true; }

bool CPU::RD(int s1, int s2, int address) {

    if(this->cpumode==debug) return false;
    if(address==0)Register[s1] = Utility::hex_to_decimal(ram->read(Register[s2] / 4 +state->job_ram_address));
    else Register[s1] = Utility::hex_to_decimal(ram->read((address) / 4 +state->job_ram_address));
}

bool CPU::WR(int s1, int s2, int address) {
    if(this->cpumode==debug) return false;
    Debug::debug(Debug::OUTPUT,"_Job "+std::to_string(state->job_id)+" outputs "+std::to_string(Register[s1]));
    ram->write(address/4, Utility::decimal_to_hex(Register[s1]));

}

bool CPU::ST(int addr, int breg, int dreg) {
//    this ->ram.write(addr,this->Register[regNum]);
    //Utility::decimal_to_hex
    if(addr==0) ram->write(Register[dreg]/4+state->job_ram_address, Utility::decimal_to_hex(Register[breg]));
    else ram->write(addr/4 +state->job_ram_address, Utility::decimal_to_hex(Register[breg]));
    return true;
}

bool CPU::LW(int addr, int breg, int dreg) {
    if(addr==0)this->Register[dreg] = Utility::hex_to_decimal(this->ram->read(Register[breg] / 4+state->job_ram_address));
    else this->Register[dreg] = Utility::hex_to_decimal(this->ram->read(addr / 4 +state->job_ram_address));
    return true;
}

bool CPU::MOV(int S1, int S2) {
    this->Register[S1] = this->Register[S2];
    return true;
}
bool CPU::ADD(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] + this->Register[S2];
    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(Register[S1])
                                 +") + R["+std::to_string(S2)+"]("+std::to_string(Register[S2])
                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::SUB(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] - this->Register[S2];
    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(Register[S1])
                                 +") - R["+std::to_string(S2)+"]("+std::to_string(Register[S2])
                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::MUL(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] * this->Register[S2];
    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(Register[S1])
                                 +") * R["+std::to_string(S2)+"]("+std::to_string(Register[S2])
                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::DIV(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] / this->Register[S2];
    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(Register[S1])
                                 +") / R["+std::to_string(S2)+"]("+std::to_string(Register[S2])
                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::AND(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] & this->Register[S2];
    return true;
}
bool CPU::OR(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] | this->Register[S2];
    return true;
}
bool CPU::MOVI(int val, int D) {
    this -> Register[D] = val;
    return true;
}
bool CPU::ADDI(int val, int D) {
    this->Register[D]+= val;
    return true;
}
bool CPU::MULI(int val, int D) {
    this->Register[D]*= val;
    return true;
}
bool CPU::DIVI(int val, int D) {
    this->Register[D]/= val;
    return true;
}
bool CPU::LDI(int val, int D) {
    this->Register[D]= val;
    return true;
}
bool CPU::SLT(int S, int B, int D) {
    this->Register[D]= (this->Register[S]<this->Register[B])?1:0;
    return true;
}
bool CPU::SLTI(int S, int val, int D) {
    this->Register[D]= (this->Register[S]<val)?1:0;
    return true;
}
bool CPU::HLT() {
    Debug::debug(Debug::SCHEDULER, "Finished a job");
    this->state->state = state->COMPLETED;
    return true; //end program?
}
bool CPU::NOP() {
    return true;
}
bool CPU::JMP(int line_no) {
    PC = line_no/4;
    return true;
}
bool CPU::BEQ(int B, int D, int addr) {
    if(this->Register[B]==this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BNE(int B, int D, int addr) {
    if(this->Register[B]!=this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BEZ(int B, int addr) {
    if(this->Register[B]==0) JMP(addr);
    return true;
}
bool CPU::BNZ(int B, int addr) {
    if(this->Register[B]!=0) JMP(addr);
    return true;
}
bool CPU::BGZ(int B, int addr) {
    if(this->Register[B]>0) JMP(addr);
    return true;
}
bool CPU::BLZ(int B, int addr) {
    if(this->Register[B]<0) JMP(addr);
    return true;
}

int *CPU::dump_registers() {
    return Register;
}

std::string CPU::fetch(int i) {
    return this->ram->read(i+state->job_ram_address);
}

Op CPU::decode(std::string hex) {
    std::string instruction = Utility::hex_to_binary(hex);
    Op inst;
    inst.op_type = instruction.substr(0,2);
    inst.op_code = Utility::binary_to_hex(instruction.substr(2, 6));
    if(inst.op_type=="00"){
        inst.sreg1 = Utility::binary_to_decimal(instruction.substr(8, 4));
        inst.sreg2 = Utility::binary_to_decimal(instruction.substr(12, 4));
        inst.dreg  = Utility::binary_to_decimal(instruction.substr(16, 4));
        inst.address = -1;
        inst.breg = -1;

    }
    else if(inst.op_type=="01"){
        inst.breg = Utility::binary_to_decimal(instruction.substr(8, 4));
        inst.dreg = Utility::binary_to_decimal(instruction.substr(12, 4));
        inst.address = Utility::binary_to_decimal(instruction.substr(16, 16));
        inst.sreg1 = -1;
        inst.sreg2 = -1;
    }
    else if(inst.op_type=="10"){
        inst.address = Utility::binary_to_decimal(instruction.substr(8, 24));
        inst.sreg1 = -1;
        inst.sreg2 = -1;
        inst.breg = -1;
        inst.dreg = -1;

    }
    else if(inst.op_type=="11"){
        inst.sreg1 = Utility::binary_to_decimal(instruction.substr(8, 4));
        inst.sreg2 = Utility::binary_to_decimal(instruction.substr(12, 4));
        inst.address  = Utility::binary_to_decimal(instruction.substr(16, 16));
        inst.breg = -1;
        inst.dreg = -1;
    }
    return inst;
}

void CPU::execute(Op op) {
    if(op.op_type=="00"){
             if(op.op_code=="04")CPU::MOV(op.sreg1,op.sreg2);
        else if(op.op_code=="05")CPU::ADD(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="06")CPU::SUB(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="07")CPU::MUL(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="08")CPU::DIV(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="09")CPU::AND(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="10")CPU::SLT(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="0A")CPU::OR(op.sreg1,op.sreg2,op.dreg);
    }else
    if(op.op_type=="01"){
             if(op.op_code=="02")CPU::ST(op.address,op.breg,op.dreg);
        else if(op.op_code=="03")CPU::LW(op.address,op.breg,op.dreg);
        else if(op.op_code=="0B")CPU::MOVI(op.address,op.dreg);
        else if(op.op_code=="0C")CPU::ADDI(op.address,op.dreg);
        else if(op.op_code=="0D")CPU::MULI(op.address,op.dreg);
        else if(op.op_code=="0E")CPU::DIVI(op.address,op.dreg);
        else if(op.op_code=="0F")CPU::LDI(op.address,op.dreg);
        else if(op.op_code=="11")CPU::SLTI(op.breg,op.address,op.dreg);
        else if(op.op_code=="15")CPU::BEQ(op.breg,op.dreg,op.address);
        else if(op.op_code=="16")CPU::BNE(op.breg,op.dreg,op.address);
        else if(op.op_code=="17")CPU::BEZ(op.breg,op.address);
        else if(op.op_code=="18")CPU::BNZ(op.breg,op.address);
        else if(op.op_code=="19")CPU::BGZ(op.breg,op.address);
        else if(op.op_code=="1A")CPU::BLZ(op.breg,op.address);
    }else
    if(op.op_type=="10"){
             if(op.op_code=="12")CPU::HLT();
        else if(op.op_code=="14")CPU::JMP(op.address);
    }else
    if(op.op_type=="11"){
             if(op.op_code=="00")CPU::RD(op.sreg1,op.sreg2,op.address);
        else if(op.op_code=="01")CPU::WR(op.sreg1,op.sreg2,op.address);
    }
}

void CPU::load_pcb(PCB *p) {
    this->state = p;
    PC = p->prgm_counter;
    this->state->state = PCB::RUNNING;
    for (int i = 0; i < 16; ++i) {
        this->Register[i] = this->state->registers[i];
    }
}
PCB* CPU::store_pcb() {
    PCB* out = state;
    if(this->state->state != PCB::COMPLETED) this->state->state = PCB::READY;
    out->prgm_counter = PC;
    for (int i = 0; i < 16; ++i) {
        this->state->registers[i] = this->Register[i];
    }
    return out;
}
void CPU::pass(std::string val) {
    Op decoded = CPU::decode(val);
    std::cout << "OpType: " << decoded.op_type << std::endl;
    std::cout << "OpCode: " << decoded.op_code << std::endl;
    std::cout << "sreg1: " << decoded.sreg1 << std::endl;
    std::cout << "sreg2: " << decoded.sreg2 << std::endl;
    std::cout << "dreg: " << decoded.dreg << std::endl;
    std::cout << "breg: " << decoded.breg << std::endl;
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
void CPU::test() {
    CPU cpu = CPU(new RAM(),debug);
    cpu.pass("C050005C");
    cpu.pass("4B060000");
    cpu.pass("4B0A0000");
    cpu.pass("4C0A0004");
}