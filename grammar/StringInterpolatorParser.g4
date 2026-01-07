parser grammar StringInterpolatorParser;

options { 
tokenVocab=StringInterpolatorLexer;
}

property_name: DOT ID ;
property_index: DOT OPENB INT CLOSEB ;
property_item: property_name | property_index;
property: DOT | property_item+ ;

variable_reference: DOLLAR ID property_item* ;

string: STRING_START ( STRING_TEXT | STRING_ESCAPE )* STRING_END ;
integer: INT ;
float: FLOAT ;
boolean: TRUE | FALSE ;
literal: string | integer | float | boolean ;

argument: expr_item | expr_block ;
arg_list: argument? ( WS+ argument )*;
func: AT? ID ( WS+ arg_list )? ;

array_item: WS* ( expr_item | expr_block ) WS* ;
array: OPENB (array_item COMMA)* (array_item)? CLOSEB ;

expr_item: literal | property | func | array | variable_reference ;
piped_expression: expr_item WS* PIPE WS* ( expr_item | piped_expression ) ;
expr: expr_item | piped_expression | expr_block ;

assign_stmt: DOLLAR ID WS* EQUAL WS* expr ;
function_parameter: ID QUESTION? ;
function_parameters: OPENP WS* ( function_parameter WS* ( COMMA WS* function_parameter WS* )* COMMA? ) WS* CLOSEP ;
function_def_stmt: AT ID WS* function_parameters? WS* ARROW WS* expr_block ;
simple_expr_stmt: expr ;
expr_stmt: ( assign_stmt | function_def_stmt | simple_expr_stmt ) WS* SEMICOLON ;

expr_block_contents: ( expr_stmt WS* )* expr ;
expr_block: OPENP WS* expr_block_contents WS* CLOSEP ;

//--------------
// Interpolation
//--------------

eval: OPEN WS* expr_block_contents WS* CLOSE ;

loop_start: OPEN HASH WS* expr_block_contents WS* CLOSE;
loop_end: OPEN SLASH SLASH WS* CLOSE ;
loop: loop_start interpolated_str loop_end;

stmt: eval | loop;

normal: ( NORMAL_TEXT | NORMAL_ESCAPE )+ ;

interpolated_str: ( normal | stmt )* ;

expression_program: WS* expr_block_contents WS* EOF;
program: interpolated_str EOF;




