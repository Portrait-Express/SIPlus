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

literal: string | integer | float ;

argument: literal | field | OPENP expr CLOSEP ;
arg_list: argument? ( argument )*;

func: ID arg_list ;

expr_item: literal | field | func;

expr: expr_item | expr PIPE expr_item;

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
