lexer grammar StringInterpolatorLexer;

NORMAL_TEXT: ~[{\\]+;
NORMAL_ESCAPE: '\\' .;
OPEN: '{' -> mode(TEMPLATE);

mode TEMPLATE;

TRUE: 'true' ;
FALSE: 'false' ;
VAR: 'var' ;
PERSIST: 'persist' ;
CONST: 'const' ;
DOT: '.' ;
HASH: '#' ;
SLASH: '/' ;
CLOSE: '}' -> mode(DEFAULT_MODE);
OPENP: '(' ;
CLOSEP: ')' ;
OPENB: '[' ;
CLOSEB: ']' ;
COMMA: ',' ;
PIPE: '|' ;
DOLLAR: '$' ;
SEMICOLON: ';' ;
QUESTION: '?' ;
AT: '@' ;
EQUAL: '=' ;
ARROW: '=>' ;
BACKSLASH: '\\' ;
STRING_START: '"' -> mode(STRING);

WS: [ \t\r\n]+;

INT: ('0'[xboXBO])?[0-9_]+ ;
FLOAT: ( [0-9]+ '.' [0-9]* ) | ( '.' [0-9]+ ) ;

ID: [a-zA-Z][a-zA-Z0-9_]*;

ANY: .;

mode STRING;

STRING_TEXT: ~["\\]+;
STRING_ESCAPE: '\\' .;
STRING_END: '"' -> mode(TEMPLATE);



















