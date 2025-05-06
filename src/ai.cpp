#include "ai.h"

/// @brief Finds the number of goals in the robot's area.
/// @return 0 = No Goals, 1 = Middle Goal, 2 = Right Goal, 3 = Both Goals
int find_Local_Goals_In_My_Area()
{
    int leftGoalNumber = 0;
    int rightGoalNumber = 0;
    ai.takeSnapshot(Goal);

    if(ai.objectCount > 0)
    {
        for (int i = 0; i < ai.objectCount; i++) 
        {
            if(ai.objects[i].originY > 100 && ai.objects[i].height > 70)
            {
                if(ai.objects[i].centerX < 160)
                    leftGoalNumber += 1;
                else if(ai.objects[i].centerX > 160)
                    rightGoalNumber += 1;
            }
        }
    }
    
    if(leftGoalNumber >= 1 && rightGoalNumber == 0)
        return 1; // Middle Goal
    else if(leftGoalNumber == 0 && rightGoalNumber >= 1)
        return 2; // Right Goal
    else if(leftGoalNumber >= 1 && rightGoalNumber >= 1)
        return 3; // Both Goals
    else
        return 0; // No Goals
}