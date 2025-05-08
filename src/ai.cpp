#include "ai.h"

Goal_AI::Goal_AI()
{
    // Default constructor
}
Goal_AI::Goal_AI(int screenHeightDeadzone, int goalScreenDivider, int goalDistanceSensitivity)
{
    this->screenHeightDeadzone = screenHeightDeadzone;
    this->goalScreenDivider = goalScreenDivider;
    this->goalDistanceSensitivity = goalDistanceSensitivity;
}

/// @brief Finds the number of goals in the robot's area.
/// @return 0 = No Goals, 1 = Middle Goal, 2 = Right Goal, 3 = Both Goals
int Goal_AI::find_Local_Goals_In_My_Area()
{
    return find_Local_Goals_In_My_Area(0);
}

/// @brief Finds the number of goals in the robot's area.
/// @return 0 = No Goals, 1 = Left Goal, 2 = Right Goal, 3 = Both Goals
int Goal_AI::find_Local_Goals_In_My_Area(int iteration)
{
    int leftGoalNumber = 0;
    int rightGoalNumber = 0;
    ai.takeSnapshot(Goal);

    if(ai.objectCount > 0)
    {
        for (int i = 0; i < ai.objectCount; i++) 
        {
            if(ai.objects[i].originY > screenHeightDeadzone && ai.objects[i].height > goalDistanceSensitivity)
            {
                if(ai.objects[i].centerX < goalScreenDivider)
                    leftGoalNumber += 1;
                else if(ai.objects[i].centerX > goalScreenDivider)
                    rightGoalNumber += 1;
            }
        }
    }
    
    if(leftGoalNumber >= 1 && rightGoalNumber == 0)
        return 1; // Left Goal
    else if(leftGoalNumber == 0 && rightGoalNumber >= 1)
        return 2; // Right Goal
    else if(leftGoalNumber >= 1 && rightGoalNumber >= 1)
        return 3; // Both Goals
    else
    {
        if(iteration < 1)
            return find_Local_Goals_In_My_Area(iteration + 1); // Try again
        else
            return 0; // No Goals
    }
}