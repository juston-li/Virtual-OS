//
//  Assembler.cpp
//  
//
//  Created by Jack Dempsey on 2/16/14.
//
//

#include "Assembler.hpp"

Assembler():op({0,0,0,0,0}),immediate(0),numRegisters(0),isAddr(false){
}
~Assember(){
}
void splitInput(const std::string &inputString, std::vector<std::string> &elems) {
    char delim = ' ';
    std::stringstream ss(inputString);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}
void getOperation(std::string operationString){
    if ((instruct == "load")||(instruct == "loadi")){
        numRegisters = 1;
        if (instruct == "loadi"){
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            op[i]=0;
        }
    }
    else if ((instruct == "store")){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if (i == 4){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "add")||(instruct == "addi")){
        numRegisters = 2;
        if (instruct == "addi"){
            immediate = 1;
            numRegisters = 1;
        }
        for (int i = 0; i < 5; ++i){
            if (i == 3){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "addc")||(instruct == "addci")){
        numRegisters = 2;
        if (instruct == "addci"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 3)||(i==4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "sub")||(instruct == "subi")){
        numRegisters = 2;
        if (instruct == "subi"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if (i == 2){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "subc")||(instruct == "subci")){
        numRegisters = 2;
        if (instruct == "subci"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "and")||(instruct == "andi")){
        numRegisters = 2;
        if (instruct == "andi"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==3)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if ((instruct == "xor")||(instruct == "xori")){
        numRegisters = 2;
        if (instruct == "xori"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==3)||(i==4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "compl"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if (i == 1){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "shl"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "shla"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 3)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "shr"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 3)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "shra"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }

    else if ((instruct == "compr")||(instruct == "compri")){
        numRegisters = 2;
        if (instruct == "compri"){
            numRegisters = 1;
            immediate = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "getstat"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 3)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "putstat"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 3)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "jump"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if (i == 0){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "jumpl"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 4)){
                op[i]) = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "jumpe"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 3)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "jumpg"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 3)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "call"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "return"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "read"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 3)){
                op[i] = 1;
            }
            else {
                iop[i]=0;
            }
        }
    }
    else if (instruct == "write"){
        numRegisters = 1;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 3)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "halt"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 1)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
    else if (instruct == "noop"){
        numRegisters = 0;
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 1)||(i == 4)){
                op[i] = 1;
            }
            else {
                op[i]=0;
            }
        }
    }
}
