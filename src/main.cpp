#include "LogAnalyzer.h"
#include <iostream>



int main(int argc,char* argv[]){
    
    if(argc!=3){
        std::cout<<"用法：./log_analyzer <日志文件> <搜索关键词>"<<std::endl;
        return 1;
    }

    LogAnalyzer loganalyzer;

    LogAnalyzer::AnalyzeResult result = loganalyzer.analyze(
        argv[1],
        argv[2]
    );

    if(!result.ok){
        return 1;
    }

    loganalyzer.print_summary(result);

    return 0;
}
