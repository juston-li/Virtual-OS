//
//  Assembler.cpp
//  
//
//  Created by Jack Dempsey on 2/16/14.
//
//

#include "Assembler.hpp"

Assembler(){
}
~Assember(){
}
vector<int> genObjectCode(std::string instruct){
    ir.at(8) = 0;
    for (i = 0; i < 6; ++i){
        ir.at(i)=0;
    }
    if ((instruct == "load")||(instruct == "loadi")){
        if (instruct == "loadi"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            ir.at(11+i)=0;
        }
    }
    else if ((instruct == "store")){
        for (int i = 0; i < 5; ++i){
            if (i == 4){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "add")||(instruct == "addi")){
        if (instruct == "addi"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if (i == 3){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "addc")||(instruct == "addci")){
        if (instruct == "addci"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 3)||(i==4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "sub")||(instruct == "subi")){
        if (instruct == "subi"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if (i == 2){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "subc")||(instruct == "subci")){
        if (instruct == "subci"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "and")||(instruct == "andi")){
        if (instruct == "andi"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==3)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "xor")||(instruct == "xori")){
        if (instruct == "xori"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 2)||(i==3)||(i==4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "compl"){
        for (int i = 0; i < 5; ++i){
            if (i == 1){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "shl"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "shla"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 3)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "shr"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 3)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "shra"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "compr"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if ((instruct == "compr")||(instruct == "compri")){
        if (instruct == "compri"){
            ir.at(8) = 1;
        }
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "getstat"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 3)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "putstat"){
        for (int i = 0; i < 5; ++i){
            if ((i == 1)||(i == 2)||(i == 3)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "jump"){
        for (int i = 0; i < 5; ++i){
            if (i == 0){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "jumpl"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "jumpe"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 3)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "jumpg"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 3)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "call"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "return"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "read"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 3)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "write"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 2)||(i == 3)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "halt"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 1)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
    else if (instruct == "noop"){
        for (int i = 0; i < 5; ++i){
            if ((i == 0)||(i == 1)||(i == 4)){
                ir.at(11+i) = 1;
            }
            else {
                ir.at(11+i)=0;
            }
        }
    }
}
