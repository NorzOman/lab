
#pragma  once

#include <string>
#include <vector>
#include <unordered_map>

struct test{
    std::string testName;
    std::string testDate;
    std::string topic;
    int obtainedMarks;
    int totalMarks;
    int obtainedDuration;
    int totalDuration;
};

struct subject{
    std::string subName;
    std::unordered_map<int,std::vector<test>> tests;
};

struct student{
    std::string studentName;
    std::string studentId;
    int rating;
    std::vector<subject> optedSubjects;
};

struct classroom{
    std::string className;
    std::string classFaculty;
    std::vector<student> batch;
};
