#ifndef TEST_Q3
#define TEST_Q3

#include <gtest/gtest.h>

class Student {
public:

    // Constructor
    Student(const std::string&);

    // Get the student's name
    std::string get_name() const;

    // Add a quiz score
    void add_quiz(const int);

    // Get the total score
    int get_total_score() const;

    // Get the average score
    double get_average_score() const;

private:

    std::string name;
    int         total_score;
    int         quiz_count;
};

class StudentTests : public ::testing::TestWithParam<std::string> {
protected:

    Student* stud;

    void SetUp() override {
        const std::string name = GetParam();
        stud                   = new Student(name);
    }

    void TearDown() override { delete stud; }
};

const auto student_names = ::testing::Values(
    "0Bionic", "adinanaveed", "ahmad-5113", "AlishbahS", "aqsa-muneer",
    "Areesha06", "Arshi-ali", "EvilDrSteve", "Hafsa-Ehsan", "huzaifa-ali05",
    "kehkashan1034", "Khanx007", "KrishKumar969", "M-AyubAnsari",
    "MaazHaris-9633", "MaleehaNasir", "miqdadhayati", "mm10016", "ms10054",
    "myrahhussain", "prabha10292", "romaisashazad", "samiasarfaraz",
    "sarah-fatima404", "sarah404-debug", "SaroshMehdi", "te-ana",
    "zainabsbhutto02");

INSTANTIATE_TEST_SUITE_P(, StudentTests, student_names);

TEST_P(StudentTests, ConstructorAndGetName) {
    const std::string expected_name = GetParam();
    EXPECT_EQ(stud->get_name(), expected_name);
}

TEST_P(StudentTests, AddQuizAndGetTotalScore) {
    stud->add_quiz(85);
    stud->add_quiz(90);
    stud->add_quiz(78);
    EXPECT_EQ(stud->get_total_score(), 253);
}

TEST_P(StudentTests, GetAverageScore) {
    stud->add_quiz(85);
    stud->add_quiz(90);
    stud->add_quiz(78);
    EXPECT_DOUBLE_EQ(stud->get_average_score(), 84.33333333333333);
}

TEST_P(StudentTests, NoQuizzes) {
    EXPECT_EQ(stud->get_total_score(), 0);
    EXPECT_DOUBLE_EQ(stud->get_average_score(), 0.0);
}

TEST_P(StudentTests, SingleQuiz) {
    stud->add_quiz(100);
    EXPECT_EQ(stud->get_total_score(), 100);
    EXPECT_DOUBLE_EQ(stud->get_average_score(), 100.0);
}

TEST_P(StudentTests, MultipleQuizzes) {
    stud->add_quiz(70);
    stud->add_quiz(80);
    stud->add_quiz(90);
    stud->add_quiz(100);
    EXPECT_EQ(stud->get_total_score(), 340);
    EXPECT_DOUBLE_EQ(stud->get_average_score(), 85.0);
}

#endif