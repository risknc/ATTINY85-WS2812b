#ifndef State_h
#define State_h
typedef void State;//statefunctions should be of this type
typedef State (*Pstate)();//pointer to statefunction
State Nop();

//macro for detection af rasing edge
#define RE(signal, state) (state=(state<<1)|(signal&1)&3)==1

//macro for detection af falling edge
#define FE(signal, state) (state=(state<<1)|(signal&1)&3)==2
#endif