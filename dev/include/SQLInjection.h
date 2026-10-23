#pragma once

#include <iostream>
#include <string>

class SQLInjection
{
private:
    bool lessonComplete = false;
    bool assessmentComplete = false;
    bool rewardClaimed = false;

    void DisplayLesson() const;
    bool RunAssessment();

public:
    void Run();

    bool IsLessonComplete() const;
    bool IsAssessmentComplete() const;
    bool IsRewardClaimed() const;

    void MarkRewardClaimed();

    void RestoreProgress(
        bool lesson,
        bool assessment,
        bool reward);
};