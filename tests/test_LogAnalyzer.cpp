
#include <gtest/gtest.h>

#include "LogAnalyzer.h"

#include <cstdio>
#include <fstream>
#include <string>

class LogAnalyzerTest : public ::testing::Test {
protected:
    LogAnalyzer analyzer;
    const std::string filename = "/tmp/log_analyzer_test.log";

    void write_log(const std::string& content) {
        std::ofstream file(filename);
        file << content;
    }

    void TearDown() override {
        std::remove(filename.c_str());
    }
};

TEST_F(LogAnalyzerTest, CountsLogLinesAndLevels) {
    write_log(
        "[INFO] system started\n"
        "[WARNING] high temperature\n"
        "[ERROR] sensor failed\n"
        "[INFO] retry sensor\n"
    );

    const auto result = analyzer.analyze(filename, "sensor");

    EXPECT_TRUE(result.ok);
    EXPECT_EQ(result.line_count, 4);
    EXPECT_EQ(result.keyword_count, 2);
    EXPECT_EQ(result.error_count, 1);
    EXPECT_EQ(result.info_count, 2);
    EXPECT_EQ(result.warning_count, 1);
    EXPECT_EQ(result.first_error_line, 3);
    EXPECT_EQ(result.keyword_lines.size(), 2u);
    EXPECT_EQ(result.error_lines.size(), 1u);
}

TEST_F(LogAnalyzerTest, ReturnsNoMatchesForMissingKeyword) {
    write_log("[INFO] system started\n[ERROR] disk failed\n");

    const auto result = analyzer.analyze(filename, "camera");

    EXPECT_TRUE(result.ok);
    EXPECT_EQ(result.keyword_count, 0);
    EXPECT_TRUE(result.keyword_lines.empty());
    EXPECT_EQ(result.error_count, 1);
}

TEST_F(LogAnalyzerTest, HandlesEmptyFile) {
    write_log("");

    const auto result = analyzer.analyze(filename, "ERROR");

    EXPECT_TRUE(result.ok);
    EXPECT_EQ(result.line_count, 0);
    EXPECT_EQ(result.keyword_count, 0);
    EXPECT_EQ(result.error_count, 0);
    EXPECT_EQ(result.first_error_line, 0);
}

TEST_F(LogAnalyzerTest, ReportsMissingFile) {
    std::remove(filename.c_str());

    const auto result = analyzer.analyze(filename, "ERROR");

    EXPECT_FALSE(result.ok);
}

TEST_F(LogAnalyzerTest, RecordsExactMatchingLines) {
    write_log(
        "[INFO] camera ready\n"
        "[ERROR] camera disconnected\n"
    );

    const auto result = analyzer.analyze(filename, "camera");

    ASSERT_EQ(result.keyword_lines.size(), 2u);
    EXPECT_EQ(result.keyword_lines[0], "第1行匹配：[INFO] camera ready");
    EXPECT_EQ(result.keyword_lines[1], "第2行匹配：[ERROR] camera disconnected");
}
