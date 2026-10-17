#pragma once

#include <string>
#include <vector>

class LogAnalyzer{
public:
    struct AnalyzeResult{
        bool ok{true};
        std::string keyword;
        int line_count{0};
        int keyword_count{0};
        int error_count{0};
        int info_count{0};
        int warning_count{0};
        int first_error_line{0};
        std::vector<std::string> keyword_lines;
        std::vector<std::string> error_lines;
    };

    AnalyzeResult analyze(
        const std::string& filename,
        const std::string& keyword
    ) const;

    void print_summary(const AnalyzeResult& result) const;

private:
    static bool is_error(const std::string& line);
    static bool is_info(const std::string& line);
    static bool is_warning(const std::string& line);
};