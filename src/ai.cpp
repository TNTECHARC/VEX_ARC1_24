#include "ai.h"


// 0 = No Goals, 1 = Middle Goal, 2 = Right Goal, 3 = Both Goals
int find_Local_Goals_In_My_Area()
{
    int GoalNumber = 0;
    ai.takeSnapshot(Goal);

    if(ai.objectCount > 0)
    {
        for (int i = 0; i < ai.objectCount; i++) 
        {
            if(ai.objects[i].originY > 100 && ai.objects[i].height > 65)
            {
                if(ai.objects[i].centerX < 160)
                    GoalNumber += 1;
                else if(ai.objects[i].centerX > 160)
                    GoalNumber += 2;
            }
        }
    }
    
    return GoalNumber;
}