//
// Created by konfe on 24.01.2026.
//
#include <gtest/gtest.h>
#include "factory.hpp"

TEST (parse_line_Test, correct_parsing_ramp) {
    std::string s = "LOADING_RAMP id=1 delivery-interval=3";
    ParsedLineData ps = parse_line(s);
    ParsedLineData pe;
    pe.element_type = ElementType::RAMP;
    pe.parameters = {{"id","1"},{"delivery-interval","3"}};
    EXPECT_EQ(ps, pe);
}
TEST (parse_line_Test, correct_parsing_worker) {
    std::string s = "WORKER id=1 processing-time=2 queue-type=FIFO";
    ParsedLineData ps = parse_line(s);
    ParsedLineData pe;
    pe.element_type = ElementType::WORKER;
    pe.parameters = {{"id","1"},{"processing-time","2"},{"queue-type","FIFO"}};
    EXPECT_EQ(ps, pe);
}
TEST (parse_line_Test, incorrect_parsing) {
    std::string s = "ERROR other=something";
    ASSERT_THROW(parse_line(s),std::invalid_argument);
}