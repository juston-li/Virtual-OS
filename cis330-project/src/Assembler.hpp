//
//  Assembler.hpp
//  
//
//  Created by Jack Dempsey on 2/16/14.
//
//

#ifndef ____Assembler__
#define ____Assembler__

#include <iostream>
class ASsembler {
public:
    Assembler::Assembler();
    Assembler::~Assember();
    vector<int> Assembler::genObjectCode(std::string instruct);
private:
    vector<int> ir(16);
};
#endif /* defined(____Assembler__) */
