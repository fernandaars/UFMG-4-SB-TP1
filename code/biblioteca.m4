dnl
pushdef(`LBL_PROG', `a')dnl
dnl
dnl
dnl
pushdef(`XXX', `c')dnl
pushdef(`XXX', `d')dnl
pushdef(`XXX', `e')dnl
pushdef(`XXX', `f')dnl
pushdef(`XXX', `g')dnl
pushdef(`XXX', `h')dnl
pushdef(`XXX', `i')dnl
pushdef(`XXX', `j')dnl
pushdef(`XXX', `k')dnl
pushdef(`XXX', `l')dnl
pushdef(`XXX', `m')dnl
pushdef(`XXX', `n')dnl
pushdef(`XXX', `o')dnl
pushdef(`XXX', `p')dnl
pushdef(`XXX', `q')dnl
pushdef(`XXX', `r')dnl
pushdef(`XXX', `s')dnl
pushdef(`XXX', `t')dnl
pushdef(`XXX', `u')dnl
pushdef(`XXX', `v')dnl
pushdef(`XXX', `w')dnl
pushdef(`XXX', `x')dnl
pushdef(`XXX', `y')dnl
dnl
dnl
dnl
define(`program', `JMP LBL_PROG
z DC 0
u DC 1')dnl
dnl
define(`begin', `LBL_PROG builtin(`popdef', `LBL_PROG')dnl')dnl
dnl
dnl
dnl
define(`ler', `INP $1')dnl
define(`escrever', `OUT $1')dnl
dnl
define(`soma', LAD $2
ADD $3
SAD $1)dnl
define(`sub', LAD $2
SUB $3
SAD $1)dnl
dnl
define(`inc', LAD $1
ADD u
SAD $1)dnl
define(`dec', LAD $1
SUB u
SAD $1)dnl
dnl
define(`clr', `LAD z
SAD $1')dnl
dnl
define(`int', `$1 DC $2')dnl
define(`end', `HLT')dnl
define(`end_program', `END')dnl
define(`end_se', `LBL_JMP builtin(`popdef', `LBL_JMP')dnl')dnl
dnl
dnl
dnl
define(`se', `LAD $1
SUB $3 
ifelse(`$2', `menor', `JGZ LBL_JMP 
JZE LBL_JMP', 
	`$2', `menor_igual', `JGZ LBL_JMP',
	`$2', `maior', `JLZ LBL_JMP
JZE LBL_JMP', 
	`$2', `maior_igual', `JLZ LBL_JMP',
	`$2', `igual', `JGE LBL_JMP'
JLE LBL_JMP)')dnl
dnl
dnl
dnl
define(`para', `JMP LBL_JMP
dnl
LBL_FOR DC $3 dnl
pushdef(`LBL_FOR_ARG', defn(`LBL_FOR'))dnl
popdef(`LBL_FOR')
dnl
LBL_FOR DC $2 dnl
pushdef(`LBL_FOR_ARG', defn(`LBL_FOR'))dnl
popdef(`LBL_FOR')
dnl
LBL_JMP popdef(`LBL_JMP')dnl
LAD LBL_FOR_ARG
SUB u
SAD $1
popdef(`LBL_JMP')dnl
LBL_JMP dnl
popdef(`LBL_FOR_ARG')dnl
SUB LBL_FOR_ARG
pushdef(`JMP_BACK_TO_LOOP', defn(`LBL_JMP'))dnl
popdef(`LBL_JMP')dnl
JZE LBL_JMP
LAD $1
ADD u
SAD $1 dnl
')dnl
dnl
define(`end_para', `JMP JMP_BACK_TO_LOOP
LBL_JMP dnl
popdef(`LBL_JMP')dnl')dnl
