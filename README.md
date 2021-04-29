# EAC-Emulator
Usermode emulation of EAC

This usermode dll is used to emulate EAC. I created it for game Enlisted but it can be used for any other game for debugging. Upon starting game without EAC launcher (directly thru game exe) inject the dll into game process. It will hook imports for LoadLibrary and GetProcAddress to redirect execution to dummy functions. Unfortunately you will get kicked after few minutes of online gameplay because of heartbeat. Before using on custom game, check which functions from EAC dll are used to add dummies and extend interface if needed.
