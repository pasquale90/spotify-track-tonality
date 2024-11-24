#include "spotifeye.h"
#include <iostream>

#include "requiresFixPaths.h"

int main(){

    Spotifeye spotifeye(credentialsFile);

    if(!spotifeye.setup_user()){
        std::cout<<"Unsuccesfull authentication, please ensure credentials are set correctly, and URL is pasted back into the console."<<std::endl;
    }
    
    return 0;
}