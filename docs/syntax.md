# Syntax


## Accessors
The simplest template simply accesses a value on an object. This is done through specifying the property name.
```
Hello, { .first_name } { .last_name }
//Hello, John Doe
```

Properties can be chained to access nested values.
```
{ .contact.email }
//example@example.com
```

You may also use array indexers to access elements of an array. The index must be a constant value. Arbitrary 
expressions are not allowed.   
```
// Note the '.' before '['
{ .orders.[0].id } { .orders.[1].id } 
//1 2
```

_**NOTE**_: Due to how arrays work (more on this, below), array indexers are linear time up to the index specified.
Therefore, try to avoid using array indexers on large lists of objects. Iterating over these arrays is explained below.

## Looping
In order to handle lists of objects easier, you may iterate over the list with a template invoked for each one.
```
{# .orders }{ .id } - { .address }
{//}
//1 - 123 some st
//2 - 234 other rd
//
```

The opening `{# ... }` expression should yield an iterable list of objects to loop over. We then specify the templated 
text to be repeated for each object, and end the template with `{//}`. ALL content between `{# ... }` and `{//}` is 
preserved, including whitespace, therefore we added a newline before `{//}` to make each entry appear on a unique row. 

## Functions
Sometimes it is useful to modify data in the template to ensure it fits a certain format. To do this, we provide several 
functions which can be used in the templates to modify the data (you can include your own custom functions, as well:
\[[see](example/function/main.cpp)\]). 
```
{ add .id 10000 } // 10001
{ gt .id 10 } // false
```

We can use the "pipe" operator to send the output of one expression to another expression.

To use functions we can use the pipe operator `|` to "pipe" the output of the last expression into a function.

```
{ .first_name } // John
{ .first_name | upper } // JOHN
{ .first_name | lower } // john
{ .first_name | substr 2 } // hn
```

The pipe operator is typically a shorthand to use the value as the first argument of the next function. Check 
each function's documentation to see how the piped value is used, as it may be treated specially to normal 
parameters, although this is uncommon and advised against.

You can also use piped expressions as parameters to functions by wrapping it with parentheses.
```
{ substr .first_name ( 0 | add 2 ) } // hn
```

_**NOTE:**_ If your parameter expression includes a space, you MUST surround it with parentheses, otherwise 
parsing may not go as expected.
```
add add 2 3 4 //Invalid
add (add 2 3) 4 //Valid - 9
```


Accessors can also be specified after a piped value.
```
{ .contact | .address } is equivalent to { .contact.address }
```

## Expression mode
Before we dive deeper into more complicated features, the other powerful feature SIPlus provides, is "Expression Parsing". 
If you call `parse_expression` instead of `parse_interpolation`, you are able to get essentially a transformer 
function which can operate on a set of input data, and spit back some amount of data.

Expressions are the template content between the `{}` braces. Some valid expressions are:
```
.x
.order.[2]
```

You can use the returned `ValueRetriever` with a set of different objects to perform the same operation on them. We use 
this for highly detailed user-specifiable filtering on lists of objects. Just ensure the output is a boolean and you have 
a super flexible filtering system with custom rules.

## Variables
In the cases that some expressions become too large and unwieldy, or if you want to reuse a value multiple times, you 
can store a value to a variable, and use it later. (Whitespace is ignored, so you may split expressions on to as many 
lines as you wish)
```
var $a = mul (.id | add 2) 10; 
div $a $a
```

We use the semicolon `;` to precede our return expression with a variable assignment. You can declare as many variables 
as you want before your final output expression. The output expression is marked with the omission of the final semicolon.
```
var $b = mul (.id | add 4) 6; 
var $a = mul (.id | add 2) 10; 
div $a $b
```

You may also specify a `const` variable which will not allow that variable to be reassigned later.

```
const var $a = 2; $a = 3; $a // Error
const var $a = 2; $a // 2
```

This does not prevent modification to the value in cases such as `set_add`.


```
const var $set = set_new;
set_add $set 2;
set_has $set 2 // true
```

Variables can also be declared `persist` which causes the value of the variable to be persisted through multiple evaluations
of the same expression. Variables that are declared with `persist` are initialized on the first evaluation of the expression,
with that context at that time. The variables are not re-initalized later, but their values will be persisted through several 
invocations.

```
persist var $a = 0; $a = add $a 1; $a // 1
                                      // 2
                                      // 3

persist const var $a = 0; $a = add $a 1; $a // error
```

You may include predefined variables by including them on the data builder by calling `with(name, data)`. These are always
implicitly declared `const`.

## Expression nesting
Expressions can also be nested in case some functions have side effects
```
$a = 2;
($a = 3; ""); //The return value here has no effect
div 6 $a // 2
```
```
($a = 3; ""); //The return value here has no effect, but must be included
div 6 $a // error: $a is not defined
```

## Custom functions
You can provide your own custom functions either in the code using the library, or in the template itself. For this 
section we will stick to writing them in the template.
```
@get_2nd_index(input) => (
    $input.[2]
);
@get_2nd_index .orders
```

The name following the `@` sign is the name of the function, then is followed by a list of parameters. If a function 
takes no parameters, the parameter list may be omitted.
```
@get_2 => ( 2 ); @get_2 // 2
```

## Array Constructs
If necessary, you can declare arbitrary arrays of data.
```
[1, 2, "3", true]
```

These follow all the same rules as normal arrays. Array indexers are not able to be specified immediately after an 
array, but can be piped on afterwards.
```
[1, 2, ($x.y | upper)].[1] //Invalid
[1, 2, ($x.y | upper)] | .[1] // 2
```
