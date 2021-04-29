# EAC-Emulator
Usermode emulation of EAC

This usermode dll is used to emulate EAC. I created it for game Enlisted but it can be used for any other game. Upon starting game without EAC launcher inject the dll. It will hook imports for LoadLibrary and GetProcAddress to redirect execution to dummy functions. Unfortunately you will get kicked after few minutes because of heartbeat (still can be used for debugging).
