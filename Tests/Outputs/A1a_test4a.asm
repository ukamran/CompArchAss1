ORG #1000
MOVLZ #FF,R7
MOVL #1F,R7
ST.b R7,R7+
LD.b R7+,R7
CEX CC,#7,#7
SETPRI #1
