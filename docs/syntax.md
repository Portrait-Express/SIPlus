# Syntax


## Accessors
The simplest action that can happen is accessing a field on an object, which is done through the property names.
```
Hello, { .first_name } { .last_name }
//Hello, John Doe
```

These can be chained to access nested properties.
```
{ .contact.email }
//example@example.com
```

You may also use array indexers to access elements of an array.
_**NOTE**_: Due to how arrays work (more on this, below), array indexers are linear time up to the index specified.
Therefore, try to avoid using array indexers on large lists of objects. Iterating over these arrays is explained below.
```
// Note the '.' before '['
{ .orders.[0].id } { .orders.[1].id } 
//1 2
```

## Looping
In order to handle lists of objects easier, you may iterate over the list with a template invoked for each one.
```
{# .orders }{ .id } - { .address }
{//}
//1 - 123 some st
//2 - 234 other rd
//
```

The first opening `{# ... }` expression (No space between `{` and `#`) should yield an iterable list of objects to loop 
over. We then specify the templated text to be repeated for each object, and end the template with `{//}`. ALL content 
between `{# ... }` and `{//}` is preserved, including whitespace, therefore we added a newline before `{//}` to make 
each entry appear on a unique row. This does mean that there will be an extra newline at the end of the text. Unfortunately
there is no workaround for this at the moment.

## Functions
Sometimes it is useful to modify some of this data in the template to ensure it follows a certain format, or otherwise.
For that we provide functions which can be used in the templates to modify the data (You can even make your own 
functions!). 
```
{ .first_name } // John
{ .first_name | upper } // JOHN
{ .first_name | lower } // john
{ .first_name | substr 2 } // hn
{ .id } // 1
{ add .id 10000 } // 10001
{ gt .id 10 } // false
```

To use functions we use the pipe operator `|` to "pipe" the output of the last expression into a function.
These functions also can take arguments, which are just space-separated lists of sub-expressions. The pipe operator
is typically simply a shorthand to use the last value as the first argument of the function. Check each functon's 
documentation to see how the piped value is used, as it may be treated specially to normal parameters, although this 
is very rare.

You can even use piped expressions as parameters to functions, by wrapping it with parentheses.
```
{ substr .first_name ( 0 | add 2 ) } // hn
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
$a = mul (.id | add 2) 10; 
div $a $a
```

We use the semicolon `;` to precede our return expression with a variable assignment. You can declare as many variables 
as you want before your final output expression. The output expression is marked with the omission of the final semicolon.
```
$b = mul (.id | add 4) 6; 
$a = mul (.id | add 2) 10; 
div $a $b
```

You may include predefined variables by including them on the data builder by calling `with(name, data)`.

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

These follow all the same rules as normal arrays. Array indexers are not able to be specified immediately after, an 
array, but can be piped on afterwards.
```
[1, 2, ($x.y | upper)] | .[1] // 2
```

## Writing a custom function 
You can add a new custom function in code by implementing a `Function`, and providing it to `context.emplace_function`.
Below is an example of a simple function that just returns the value of the first parameter.
```cpp
#include <siplus/function.h>
#include <siplus/util.h>

using namespace SIPlus;

struct test_impl : public text::ValueRetriever {
    test_impl(std::shared_ptr<text::ValueRetriever> nested) : nested_(nested) {}

    text::UnknownDataTypeContainer retrieve(InvocationContext& ctx) const override {
        return nested_->retrieve(ctx);
    }

private:
    std::shared_ptr<text::ValueRetriever> nested_;
};

struct test_func : public Function {
    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, // "parent" is the piped value if it was provided
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        /**
         * get_parameters_first_parent() is a utility function provided, that returns a 
         * number of parameters, using the parent as the first parameter if it was specififed.
         * It returns a tuple of the size the template parameter specifies, of parameters.
         * You can provide a second template argument to provide a maximum number of additional 
         * optional parameters
         */
        auto [ input ] = util::get_parameters_first_parent<1>(parent, parameters);

        //Instead of above you could do ********
        std::shared_ptr<text::ValueRetriever> input;
        if(parent) {
            input = parent;
        } else {
            if(parameters.size() != 1) {
                throw std::runtime_error{"not enough parameters for 'test'"};
            }
            input = parameters[1];
        }
        //**************************************

        return std::make_shared<test_impl>(input);
    }
};

int main() {
    Parser p;
    p.context().emplace_function<test_func>();
}
```

We break functions into two steps so that we can do parameter validation at time of parsing the expression. This allows
execution to be (slightly) faster since we dont have to do redundant parameter count checks at invocation. 

This does mean adding variadic arguments later if wanted will be non-trivial.

