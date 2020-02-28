#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include"cusp.h"


namespace inputHandler{


    //returns the solution name after validation
    std::string solutionName(){
        std::string input;
        bool isValid=true;
        do{
            input=std::move(cusp::getSolutionName());
            isValid= util::assert_validity( [](const std::string& input){
                    return input.length() ;
                },input );
            if(!isValid){
                __SET_PATTERN_COL__;
                LOG_WARNING("Invalid Solution Name\n");  
            }
        } while (!isValid);
        return input;
    }
    
    //return the project name if entered. Returns solution's name if omitted
    std::string projectName(const std::string& solName){
        std::string input = cusp::getProjectName();
        return input.length() ? input : solName;
    }

    std::string author(){ return cusp::getAuthorName();}

    std::string architecture(){
        std::string input;
        bool isValid=true;
        do{
            input = cusp::getTargetArchitecture();
            isValid=util::assert_validity([](const std::string& input){
                return input=="x86"         ||      input == "32bit" 
                                            ||      
                       input=="x86_64"      ||      input == "64bit";
            },input);
            if(!isValid){
                __SET_PATTERN_COL__;
                LOG_ERROR("Invalid Entry\n");
            }
        } while(!isValid);
        return input;
    }

    std::string cppDialect(){
        std::string input;
        bool isValid=true;
        do{
            input = cusp::getLanguageDialect();
            isValid=util::assert_validity([](const std::string& input){
                return input=="c++98"     ||    input == "c++11" 
                                          ||    
                       input=="c++14"     ||    input == "c++17";
            },input);
            if(!isValid){
                __SET_PATTERN_COL__;
                LOG_ERROR("Invalid Entry\n");
            }
        } while(!isValid);
        return input;
    }

    std::string kind(){
        std::string input;
        bool isValid=true;
        do{
            input = cusp::getKindOfProject();
            isValid=util::assert_validity([](const std::string& input){
                return input=="consoleapp"     ||    input == "staticlib" 
                                               ||    
                                          input=="sharedlib";
            }, input);
            if(!isValid){
                __SET_PATTERN_COL__;
                LOG_ERROR("Invalid Entry\n");
            }
        } while(!isValid);
        return input;
    }

    std::vector<std::string> libsTolinks(){
        std::vector<std::string> libs;
        std::string input;
        do
        {
            input= cusp::getLibsToLinksAgainst();
            if(input != "-1"){
                libs.push_back(input);
            }
        } while (input!="-1");
        return libs;
    }

    std::string MITLicense(const std::string& year, const std::string& author){
        if(!cusp::shouldaddMITLicense())
            return std::string();
        else{
            std::stringstream stream;
            stream <<   "MIT License\n"
                        "Copyright (c) " <<year<<" " <<author<<"\n"

            "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
            "of this software and associated documentation files (the \"Software\"), to deal\n"
            "in the Software without restriction, including without limitation the rights\n"
            "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
            "copies of the Software, and to permit persons to whom the Software is\n"
            "furnished to do so, subject to the following conditions:\n"
            "The above copyright notice and this permission notice shall be included in all\n"
            "copies or substantial portions of the Software.\n"
            "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
            "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
            "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
            "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
            "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
            "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
            "SOFTWARE."<<std::endl;
            return stream.str();
        }
    }
}

#endif //INPUT_HANDLER_H