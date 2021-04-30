# EAC-Emulator
Usermode emulation of x64 EAC

This usermode x64 dll is used to emulate x64 EAC. I created it for game Enlisted but it can be used for any other game for debugging. Upon starting game without EAC launcher (directly thru game exe) inject the dll into game process. It will hook imports for LoadLibrary and GetProcAddress to redirect execution to dummy functions. Unfortunately you will get kicked after few minutes of online gameplay because of heartbeat. Before using on custom game, check which functions from EAC dll are used to add their dummies in GetProcAddress hook and extend interface(s) if needed.
