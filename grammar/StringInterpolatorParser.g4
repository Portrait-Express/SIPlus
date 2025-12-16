parser grammar StringInterpolatorParser;

options { 
tokenVocab=StringInterpolatorLexer;
}

property_name: DOT ID ;
property_index: DOT OPENB INT CLOSEB ;
property_item: property_name | property_index;
property: DOT | property_item+ ;

string: STRING_START ( STRING_TEXT | STRING_ESCAPE )* STRING_END ;
integer: INT ;
float: FLOAT ;
boolean: TRUE | FALSE ;

literal: string | integer | float | boolean ;

argument: expr_item | OPENP WS* ( expr_item | piped_expression ) WS* CLOSEP ;
arg_list: argument? ( WS+ argument )*;

func: ID ( WS+ arg_list )? ;

array_item: WS* ( expr | OPENP WS* expr WS* CLOSEP ) WS* ;
array: OPENB (array_item COMMA)* (array_item)? CLOSEB ;

expr_item: literal | property | func | array ;

piped_expression: expr_item WS* PIPE WS* expr ;

expr: expr_item | piped_expression;

eval: OPEN WS* expr WS* CLOSE ;

loop_start: OPEN HASH WS* expr WS* CLOSE;
loop_end: OPEN SLASH SLASH WS* CLOSE ;
loop: loop_start interpolated_str loop_end;

stmt: eval | loop;

normal: ( NORMAL_TEXT | NORMAL_ESCAPE )+ ;

interpolated_str: ( normal | stmt )* ;

expression_program: WS* expr WS* EOF;
program: interpolated_str EOF;


