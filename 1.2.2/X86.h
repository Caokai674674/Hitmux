#ifndef X86_H
#define X86_H

#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <stdlib.h>

using namespace std;

class CPU {
public:
    CPU():eax(0),ebx(0),ecx(0),edx(0) {}
    void execute(const string& instruction) {
        auto it=instructionSet.find(instruction);
        if(it!=instructionSet.end()) it->second();
        else cerr<<"Unknown instruction: "<<instruction<<endl;
    }
    void add() { eax+=ebx; cout<<"ADD: EAX = "<<eax<<endl; }
    void sub() { eax-=ebx; cout<<"SUB: EAX = "<<eax<<endl; }
    void mov() { eax=ebx; cout<<"MOV: EAX = "<<eax<<endl; }
    void mul() { eax*=ebx; cout<<"MUL: EAX = "<<eax<<endl; }
    void div() {
        if(ebx!=0) { eax/=ebx; cout<<"DIV: EAX = "<<eax<<endl; }
        else cerr<<"Error: Division by zero"<<endl;
    }
    void andOp() { eax&=ebx; cout<<"AND: EAX = "<<eax<<endl; }
    void orOp() { eax|=ebx; cout<<"OR: EAX = "<<eax<<endl; }
    void xorOp() { eax^=ebx; cout<<"XOR: EAX = "<<eax<<endl; }
    void notOp() { eax=~eax; cout<<"NOT: EAX = "<<eax<<endl; }
    void shl() { eax<<=1; cout<<"SHL: EAX = "<<eax<<endl; }
    void shr() { eax>>=1; cout<<"SHR: EAX = "<<eax<<endl; }
    void setEAX(int value) { eax=value; cout<<"SET EAX: EAX = "<<eax<<endl; }
    void setEBX(int value) { ebx=value; cout<<"SET EBX: EBX = "<<ebx<<endl; }
private:
    int eax,ebx,ecx,edx;
    unordered_map<string,function<void()>> instructionSet={
        {"ADD",[this]() { add(); }},
        {"SUB",[this]() { sub(); }},
        {"MOV",[this]() { mov(); }},
        {"MUL",[this]() { mul(); }},
        {"DIV",[this]() { div(); }},
        {"AND",[this]() { andOp(); }},
        {"OR",[this]() { orOp(); }},
        {"XOR",[this]() { xorOp(); }},
        {"NOT",[this]() { notOp(); }},
        {"SHL",[this]() { shl(); }},
        {"SHR",[this]() { shr(); }}
    };
};
void x86_f() {
	system("cls");
	cout<<"x86 Emulator 1.0-beta (C) 2024 CaoKai,All right reserved.\n";
    CPU cpu;
    string command;
    cout<<"Enter commands (ADD, SUB, MOV, MUL, DIV, AND, OR, XOR, NOT, SHL, SHR, SET_EAX, SET_EBX, or \"//exit\" to quit):"<<endl;
    while(true) {
        cout<<">> ";
        cin>>command;
        if(command=="//exit") break;
        else if(command=="SET_EAX") { int value; cout<<"Enter value for EAX: "; cin>>value; cpu.setEAX(value); }
        else if(command=="SET_EBX") { int value; cout<<"Enter value for EBX: "; cin>>value; cpu.setEBX(value); }
        else cpu.execute(command);
    }
    return;
}
#endif
