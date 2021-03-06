//
// Created by Cédric Meukens on 06/10/2021.
//

#ifndef GOINTERPRETER_MAIN_HPP
#define GOINTERPRETER_MAIN_HPP

#include <iostream>
#include "lexing/lexer.hpp"
#include "ast/ast.hpp"
#include "validation/validator.hpp"
#include "interpreter/interpreter.hpp"
extern int yyparse();
extern AST::Node *tree;

#endif //GOINTERPRETER_MAIN_HPP
