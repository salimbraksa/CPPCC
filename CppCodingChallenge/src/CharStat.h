#pragma once

#define EXP_BEGIN_CHAR CharStat::begin// the begin of expression
#define OPERAND_CHAR CharStat::num// number
#define OPERATOR_CHAR CharStat::oper// operator + = * /
#define OPEN_PARENT_CHAR CharStat::openPar// (
#define CLOSE_PARENT_CHAR CharStat::closePar// )

enum CharStat { begin, num, oper, openPar, closePar };
