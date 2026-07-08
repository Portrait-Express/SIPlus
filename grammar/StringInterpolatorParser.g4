parser grammar StringInterpolatorParser;

options { 
tokenVocab=StringInterpolatorLexer;
}

string: STRING_START ( STRING_TEXT | STRING_ESCAPE )* STRING_END ;
integer: INT ;
float: FLOAT ;
boolean: TRUE | FALSE ;
null: NULL ;
primitive: string | integer | float | boolean | null ;

array: OPENB WS* ( expr ( WS* COMMA WS* expr )* )? WS* CLOSEB ;

accessor: DOT WS* ID ;
indexer: OPENB WS* expr WS* CLOSEB ;

variable: DOLLAR ID ;
literal: primitive | array ;

call: AT? ID ( WS+ expr )* ;

variable_declaration: ( PERSIST WS+ )? ( CONST WS+ )? VAR WS+ DOLLAR ID ( WS* EQUAL WS* expr )? ;
variable_assignment: DOLLAR ID WS* EQUAL WS* expr ;
    
function_parameter: ID QUESTION? ;
function_parameters: OPENP 
        WS* function_parameter WS*
        ( COMMA WS* function_parameter WS* )* COMMA? 
    WS* CLOSEP ;
function_definition: AT ID WS* function_parameters? WS* ARROW 
    WS* expr ;

piped_suffixable_expr: accessor | DOT indexer ;

piped_expr_part: call | piped_suffixable_expr ( WS* expr_suffix )* ;
piped_expr: expr ( WS* PIPE WS* piped_expr_part )+ ;

suffixable_expr: literal
    | variable
    | block 
    | piped_suffixable_expr ;

expr_suffix: accessor | indexer ;
    
expr: suffixable_expr ( WS* expr_suffix )*
    | variable_assignment
    | call 
    | DOT ;

block_stmt: expr 
    | piped_expr
    | variable_declaration
    | function_definition ;

block_expr: expr | piped_expr ;
block_contents: ( block_stmt WS* SEMICOLON WS* )* block_expr ;
block: OPENP WS* block_contents WS* CLOSEP ;

expression_program: WS* block_contents WS* EOF;

//--------------
// Interpolation
//--------------

interp_eval: OPEN WS* block_contents WS* CLOSE ;

interp_loop_start: OPEN HASH WS* block_contents WS* CLOSE;
interp_loop_end: OPEN SLASH SLASH WS* CLOSE ;
interp_loop: interp_loop_start interpolated_str interp_loop_end;

interp_stmt: interp_eval | interp_loop;

interp_normal: ( NORMAL_TEXT | NORMAL_ESCAPE )+ ;

interp_part: interp_normal | interp_stmt ;

interpolated_str: interp_part* ;

program: interpolated_str EOF;






