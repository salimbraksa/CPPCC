#pragma once

#define EXP_BEGIN_CHAR CharStat::begin
#define OPERAND_CHAR CharStat::num
#define OPERATOR_CHAR CharStat::oper
#define OPEN_PARENT_CHAR CharStat::openPar
#define CLOSE_PARENT_CHAR CharStat::closePar

enum CharStat { begin, num, oper, openPar, closePar };
