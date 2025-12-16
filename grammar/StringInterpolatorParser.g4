parser grammar StringInterpolatorParser;

options { 
tokenVocab=StringInterpolatorLexer; 
superClass='SIPLUS_NAMESPACE::internal::SIParser';
}

@header {
#include "../si_parser.h"
}


field: {enableChannel(antlr4::Token::HIDDEN_CHANNEL);} DOT ( ID ( DOT ID )* )? {disableChannel(antlr4::Token::HIDDEN_CHANNEL);};

string: STRING_START ( STRING_TEXT | STRING_ESCAPE )* STRING_END ;
integer: INT ;
float: FLOAT ;
boolean: TRUE | FALSE ;

literal: string | integer | float | boolean ;

argument: expr_item | OPENP piped_expression CLOSEP ;
arg_list: argument? ( argument )*;

func: ID arg_list ;

array_item: expr | OPENP expr CLOSEP ;
array: OPENB (array_item COMMA)* (array_item)? CLOSEB ;

expr_item: literal | field | func | array ;

piped_expression: expr_item PIPE expr ;

expr: expr_item | piped_expression;

eval: OPEN expr CLOSE ;

loop_start: OPEN HASH expr CLOSE;
loop_end: OPEN SLASH SLASH CLOSE ;
loop: loop_start interpolated_str loop_end;

stmt: eval
    | loop;

normal: ( NORMAL_TEXT | NORMAL_ESCAPE )+ ;

interpolated_str: ( normal | stmt )* ;

expression_program: expr EOF;
program: interpolated_str EOF;

