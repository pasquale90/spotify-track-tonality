#include "spotifeye.h"
#include <filesystem>
#include <iostream>
#include <string>

#include "requiresFixPaths.h"

int main(){

    Spotifeye spotifeye(credentialsFile);

    std::vector<std::string> result(4,"");
    if(spotifeye.update_result(result)){
        std::cout<<"Result:"<<std::endl;
        std::cout<<"\tArtist:"<<result[0]<<std::endl;
        std::cout<<"\tTrack:"<<result[1]<<std::endl;
        std::cout<<"\tKey:"<<result[2]<<std::endl;
        std::cout<<"\tMode:"<<result[3]<<std::endl;
    } else{
        std::cout<<"No track is currently playing"<<std::endl;
    }
    
    
    return 0;
}