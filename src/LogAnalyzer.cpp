#include "LogAnalyzer.h"

#include <iostream>
#include <fstream>


bool LogAnalyzer::is_error(const std::string& line) {
    return line.find("ERROR") != std::string::npos;
}

bool LogAnalyzer::is_info(const std::string& line) {
    return line.find("INFO") != std::string::npos;
}

bool LogAnalyzer::is_warning(const std::string& line) {
    return line.find("WARNING") != std::string::npos;
}

void LogAnalyzer::print_summary(const AnalyzeResult& result) const{

    for(const std::string& item:result.keyword_lines){
        std::cout<<item<<std::endl;
    }
    if (result.keyword_count == 0) {
        std::cout << "没有找到关键词：" << result.keyword << std::endl;
    }
    for(const std::string& item:result.error_lines){
        std::cout<<item<<std::endl;
    }
    std::cout<<"总行数："<< result.line_count <<std::endl;
    std::cout<<"关键词数量："<< result.keyword_count<<std::endl;
    std::cout<<"错误数量："<< result.error_count <<std::endl;
    std::cout<<"信息数量："<< result.info_count <<std::endl;
    std::cout<<"警告数量："<< result.warning_count <<std::endl;
    if(result.line_count>0){
        double error_rate = static_cast<double>(result.error_count)/result.line_count*100;
        std::cout<<"错误占比："<< error_rate <<"%"<<std::endl;
    }
    if(result.first_error_line!=0){
        std::cout<<"第一个错误出现在第"<<result.first_error_line<<"行"<<std::endl;
    }
    
}

LogAnalyzer::AnalyzeResult LogAnalyzer::analyze(
        const std::string& filename,
        const std::string& keyword
) const{
    AnalyzeResult result;
    result.keyword = keyword;

    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout<<"无法打开文件！"<<std::endl;

        return result;
    }

    std::string line;
    while(std::getline(file,line)){

        ++result.line_count;

        if(line.find(keyword)!=std::string::npos){
            ++result.keyword_count;
            result.keyword_lines.push_back(
                "第"+std::to_string(result.line_count)+"行匹配："+line
            );
        }

        if(LogAnalyzer::is_error(line)){
            ++result.error_count;
            if(result.first_error_line==0){
                result.first_error_line=result.line_count;
            }
            result.error_lines.push_back(
                "第"+std::to_string(result.line_count)+"行发现错误："+line
            );
        }

        if(LogAnalyzer::is_info(line)){
            ++result.info_count;
        }

        if(LogAnalyzer::is_warning(line)){
            ++result.warning_count;
        }
    }
    file.close();
    result.ok = true;
    return result;
}

