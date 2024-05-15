#include <string> //decode 16 bit encoded title
#include <iostream> //printing and debugging
#include <stdio.h> //file management
#include <vector> //vectors cuz im too lazy to do it with an array
#include <string.h>
enum dt{
  dec,
  boo,
  str
};

typedef struct{
    std::string thing;
    int size;
    int spot;
    dt dtype;
}block;
std::vector<block*> blocks;
void defblock(std::string purpose, int size, int locale,dt dtype){
    blocks.push_back(new block{purpose,size,locale,dtype});
} //adds a location to fseek and its purpose;
int main()
{
    defblock("Game title:",12,0,str);
    defblock("Gamecode:",4,12,dec);
    defblock("Makercode:",4,16,dec);
    defblock("Rom size:",4,128,dec);
    defblock("Header size:",4,132,dec);
    std::string inp;
    FILE *rom;
        std::cout << "Enter filename/path\n";
    do{
        std::cin >> inp;
        rom = fopen(inp.c_str(),"rb");
        if(rom == NULL){
        perror("Err");
    }}
    while(rom == NULL);
    //there's probably a more efficient way to do the following loop but im not experienced enough
    for(auto b: blocks){
        fseek(rom,b->spot,SEEK_SET);
        std::cout << b->thing << " ";
        if(b->dtype ==0){
                int rbi;
                fread(&rbi,b->size,1,rom);
                std::cout << rbi << std::endl;
        }
        else if(b->dtype == 1){
                bool rbb;
                fread(&rbb,b->size,1,rom);
                std::cout << rbb << std::endl;
        }else if(b->dtype == 2){
                char *rb;
                rb = new char[b->size];
                fread(rb,1,b->size,rom);
                for(int i = 0; i < b->size; i++){
                    std::cout << rb[i];
                }
                std::cout << std::endl;
                //may not work. either that or the rom i did it with didn't include a title in its Header
                //plz test and tell me if it works if not help fix it if you want
        }
        }
    
    fclose(rom);

    return 0;
}
