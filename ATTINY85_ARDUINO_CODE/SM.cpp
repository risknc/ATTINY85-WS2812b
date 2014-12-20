#include "SM.h"

SM::SM(Pstate Initial){//create simple SM
  Set(Initial);//set initial state
}//constructor

//create SM with initial head and body states
SM::SM(Pstate First, Pstate Rest){
  Set(First, Rest);//set initial head and body state functions
}//constructor

void SM::Set(Pstate Current){
  Finished = false;//clear flag, just in case
  Body = Current;//common head-
  Head = Current;//-and body state function
  Exec = &SM::FRun;//set runstate to entry
}//Set()

void SM::Set(Pstate First, Pstate Rest){
  Finished = false;//clear flag just in case
  Head = First;//separate head-
  Body = Rest;//-and body state functions
  Exec =&SM::FRun;//set runstate to entry
}//set()

void SM::Finish(){
  Exec = &SM::Idle;//set runstate to finished
  Finished = true;//set flag
}//Finish()

void SM::Restart(){
  Exec = &SM::FRun;//set runstate to entry
  Finished = false;//clear flag
}//restart

void SM::Idle(){
  return;//do abolutely nothing
}//Idle()

State Nop(){
}


