#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_error(const std::string& line){
    return line.find("ERROR")!=std::string::npos;
}
bool is_info(const std::string& line){
    return line.find("INFO")!=std::string::npos;
}
bool is_warning(const std::string& line){
    return line.find("WARNING")!=std::string::npos;
}

void print_summary(
    int line_count,
    int keyword_count,
    int error_count,
    int info_count,
    int warning_count,
    int first_error_line
){
    std::cout<<"总行数："<< line_count <<std::endl;
    std::cout<<"关键词数量："<< keyword_count<<std::endl;
    std::cout<<"错误数量："<< error_count <<std::endl;
    std::cout<<"信息数量："<< info_count <<std::endl;
    std::cout<<"警告数量："<< warning_count <<std::endl;
    if(error_count>0){
        double error_rate = static_cast<double>(error_count)/line_count*100;
        std::cout<<"错误占比："<< error_rate <<"%"<<std::endl;
    }
    if(first_error_line!=0){
        std::cout<<"第一个错误出现在第"<<first_error_line<<"行"<<std::endl;
    }
}
int main(int argc,char* argv[]){
    
    if(argc!=3){
        std::cout<<"用法：./log_analyzer<日志文件><搜索关键词>"<<std::endl;
        return 1;
    }
    std::string keyword = argv[2];
    std::ifstream file(argv[1]);

    if(!file.is_open()){
        std::cout<<"无法打开文件！"<<std::endl;

        return 1;
    }
    
    std::string line;
    std::vector<std::string> error_lines;
    std::vector<std::string> keyword_lines;
    int line_count = 0;
    int keyword_count = 0;
    int error_count = 0;
    int info_count = 0;
    int warning_count = 0;
    int first_error_line = 0;
    

    while(std::getline(file,line)){

        ++line_count;

        if(line.find(keyword)!=std::string::npos){
            ++keyword_count;
            keyword_lines.push_back(
                "第"+std::to_string(line_count)+"行匹配："+line
            );
        }

        if(is_error(line)){
            ++error_count;
            if(first_error_line==0){
                first_error_line=line_count;
            }
            error_lines.push_back(
                "第"+std::to_string(line_count)+"行发现错误："+line
            );
        }

        if(is_info(line)){
            ++info_count;
        }

        if(is_warning(line)){
            ++warning_count;
        }
        
    }
    for(const std::string& result:keyword_lines){
        std::cout<<result<<std::endl;
    }
    for(const std::string& result:error_lines){
        std::cout<<result<<std::endl;
    }
    if (keyword_count == 0) {
        std::cout << "没有找到关键词：" << keyword << std::endl;
    }

    print_summary(
    line_count,
    keyword_count,
    error_count,
    info_count,
    warning_count,
    first_error_line
    );
    
    file.close();
    
    return 0;
}
