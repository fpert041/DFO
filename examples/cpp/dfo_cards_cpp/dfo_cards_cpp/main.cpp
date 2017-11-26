//
//  main.cpp
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include <iostream>
#include "dfo_game.h"

int main(int argc, const char * argv[]) {

    //------------
    
    Dfo_game game;
    
    game.setup();
    
    game.run();
    
    //------------
    
    return 0;
}
