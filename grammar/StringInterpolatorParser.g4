parser grammar StringInterpolatorParser;

options { 
tokenVocab=StringInterpolatorLexer; 
superClass='SIPLUS_NAMESPACE::internal::SIParser';
}

@header {
#include "../si_parser.h"
}


property_name: DOT ID ;
property_index: DOT OPENB INT CLOSEB ;
property_item: property_name | property_index;
property: {enableChannel(antlr4::Token::HIDDEN_CHANNEL);} DOT | property_item+ {disableChannel(antlr4::Token::HIDDEN_CHANNEL);};

string: STRING_START ( STRING_TEXT | STRING_ESCAPE )* STRING_END ;
integer: INT ;
float: FLOAT ;
boolean: TRUE | FALSE ;

literal: string | integer | float | boolean ;

argument: literal | property | array | OPENP piped_expression CLOSEP ;
arg_list: argument? ( argument )*;

func: ID arg_list ;

array_item: expr | OPENP expr CLOSEP ;
array: OPENB (array_item COMMA)* (array_item)? CLOSEB ;

expr_item: literal | property | func | array ;

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


