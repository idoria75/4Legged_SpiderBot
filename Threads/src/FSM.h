#pragma once

// FSM (Finite-State Machine)
// State #0: SetUp
// State #1: Reset Stance
// State #2: Initial Robot Configuration
// State #3: Move B Forward (04)
// State #4: Move A Forward (15)
// State #5: Push Forward
// State #6: Move C Forward (26)
// State #7: Move D Forward (13)
// State #8: Push Forward -> Loop back to State #3

void updateStateMachine();
void runStateMachine();