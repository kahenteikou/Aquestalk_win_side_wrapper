#include "main.hpp"

int main(int argc,char* argv[]){
    int opt;
    int speed=0;
    std::string inputfile="";
    std::string outputfile="";
    std::string dll_path="";
    while((opt=getopt(argc,argv,"hs:i:o:d:")) != -1){
        switch(opt){
            case 'h':
                usage();
                return -1;
            case 's':
                speed=atoi(optarg);
                break;
            case 'i':
                inputfile=optarg;
                break;
            case 'o':
                outputfile=optarg;
                break;
            case 'd':
                dll_path=optarg;
                break;
            case '?':
                usage();
                return -1;
        }
    }
    if(speed==0){
        std::cerr << "Missing speed" << std::endl;
        usage();
        return -1;
    }
    if(inputfile == ""){
        std::cerr << "Missing Input" << std::endl;
        usage();
        return -1;
    }
    if(outputfile == ""){
        std::cerr << "Missing Output" << std::endl;
        usage();
        return -1;
    }
    if(dll_path == ""){
        std::cerr << "Missing Dll" << std::endl;
        usage();
        return -1;
    }
    HMODULE dll = LoadLibraryA(dll_path.c_str());
    if(dll==NULL){
        std::cerr << "Failed load AquesTalk" << std::endl;
        return -810;
    }
    
    std::fstream fskun(inputfile,std::ios::in);
    if(!fskun){
        std::cerr << "Error ! Can't open "<< inputfile << std::endl;
        return -1;
    }
    std::string datakun;
    fskun >> datakun;
    fskun.close();
    int size;
    LPFNAquesTalk_Synthe AquesTalk_Synthe=0;
    AquesTalk_Synthe=(LPFNAquesTalk_Synthe)GetProcAddress(dll,"AquesTalk_Synthe");
    if(AquesTalk_Synthe == 0){
        std::cerr << "Can't call AquesTalk_Synthe" << std::endl;
        FreeLibrary(dll);
        return -4;
    }
    unsigned char* wavdata=(*AquesTalk_Synthe)(datakun.c_str(),speed,&size);

    std::fstream out_stream(outputfile,std::ios::out | std::ios::binary);
    if(!out_stream){
        std::cerr << "Error ! Can't open " << outputfile << std::endl;
        return -2;
    }
    out_stream.write((char*)wavdata,size);
    LPFNAquesTalk_FreeWave FreeWave=0;
    FreeWave=(LPFNAquesTalk_FreeWave)GetProcAddress(dll,"AquesTalk_FreeWave");
    if(FreeWave == 0){
        std::cerr << "Can't call AquesTalk_FreeWave" << std::endl;
        FreeLibrary(dll);
        return -5;
    }
    (*FreeWave)(wavdata);
    FreeLibrary(dll);
    out_stream.close();
    std::cout << "Generate Wave File : " << outputfile << std::endl;
    return 0;
}
void usage(){
    std::cout << "Usage:" << std::endl;
    std::cout << "\taquestalk_wrapper_win.exe -s [speed] -i [inputfile] -o [output file] -d [dllpath]" << std::endl;
}