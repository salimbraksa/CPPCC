#pragma once

#define EXP_BEGIN CharStat::begin
#define OPERAND CharStat::num
#define OPERATOR CharStat::oper
#define OPEN_PARENT CharStat::openPar
#define CLOSE_PARENT CharStat::closePar

enum CharStat { begin, num, oper, openPar, closePar };
