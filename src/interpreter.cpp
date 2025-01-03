#include "tokenizer.cpp"

class interpreter{
    std::string string;
    std::queue<std::string> Strings;
    std::queue<char> Chars;
    public:
    interpreter(std::string input){
        this->string = processInput(input);
        std::cout << string;
    }
    ~interpreter(){}
    std::string processInput(std::string input){
        input+="\n";
        while(eraseBetween(input, "/*", "*/")); 
        while(eraseBetween(input, "//", "\n"));
        string = replaceBetween(input, "\"", "\"", " ~STRING ");
        while(string!=""){
            Strings.push(string);
            string = replaceBetween(input, "\"", "\"", " ~STRING ");
            }
        string = replaceBetween(input, "'", "'", " ~CHAR ");
        while(string!=""){
            processChar();
            string = replaceBetween(input, "'", "'", " ~CHAR ");
        }
        return input;
    }
    void processChar(){
        if(string.length()>=1){
            if(string.length()==1){
                Chars.push(string[0]);
            } else if(string.length()==2 && string[0]=='\\'){
                Chars.push(processBackSlash(string));
            } else{
                std::cerr<<"char too long "<<string.length()<<"\n";
            }
        } else {
            std::cerr<<"char too short '"<<string<<"'\n";
            Chars.push('\0');
        }
    }
    char processBackSlash(std::string input){
        if(input[1]=='n'){
            return '\n';
        } else if(input[1]=='n'){
            return '\n';
        } else if(input[1]=='n'){
            return '\n';
        } else if(input[1]=='n'){
            return '\n';
        } else if(input[1]=='n'){
            return '\n';
        } else {
            return input[1];
        }
    }
};  