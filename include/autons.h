#pragma once
#include "JAR-Template/drive.h"

class Drive;
class ClawMech;

extern Drive chassis;
extern ClawMech claw;

void default_constants();

// Blue Autons
void blue_front_neg();
void blue_middle_neg();
void blue_back_neg();

// Red Autons
void red_front_pos();
void red_middle_pos();
void red_back_pos();
