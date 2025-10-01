lexer grammar StringInterpolatorLexer;

NORMAL_TEXT: ~[{\\]+;
NORMAL_ESCAPE: '\\' .;
OPEN: '{' -> mode(TEMPLATE);

mode TEMPLATE;

TRUE: 'true' ;
FALSE: 'false' ;
DOT: '.' ;
HASH: '#' ;
SLASH: '/' ;
CLOSE: '}' -> mode(DEFAULT_MODE);
OPENP: '(' ;
CLOSEP: ')' ;
PIPE: '|' ;
BACKSLASH: '\\' ;
STRING_START: '"' -> mode(STRING);

WS: [ \t\r\n]+ -> channel(HIDDEN);

INT: ('0'[xboXBO])?[0-9_]+ ;
FLOAT: ( [0-9]+ '.' [0-9]* ) | ( '.' [0-9]+ ) ;

ID: [a-zA-Z][a-zA-Z0-9_]*;

ANY: .;

mode STRING;

STRING_TEXT: ~["\\]+;
STRING_ESCAPE: '\\' .;
STRING_END: '"' -> mode(TEMPLATE);



















