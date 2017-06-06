#include <vector>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
}

int main(){
    
    const long long int GB_size = 1UL<<30;

    char sum = 0;
    for(int i=1; i<200; i++){
        std::cout<<"Alocating "<<i<<"GB"<<std::endl;
        std::vector<char> vec(i*GB_size,5);
        
        //just to prevent compiler optimization from eliminating the allocation
        sum += vec[rand()%vec.size()];

        std::cout<<"$>free -g"<<std::endl<<exec("free -g")<<std::endl;
    }
    
    return 0;
}
