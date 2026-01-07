# Functions
Below is a list of functions and their expected paramers. The piped value will 
be used as the first parameter for all functions unless otherwise specified.

## str
Interprets a value as a string.

- `input` any type which can be converted to a string

```
2 | str // "2"
```

## if
Returns a value based on a boolean condition. If `input` is `true` returns 
`value`, otherwise returns `else`.

- `input` boolean value
- `value` any value
- `else` any value

```
if true 2 3 // 2
if false 2 3 // 3
```

## map
Maps over an iterable list performing a transform in each item and yielding a 
new list

- `input` an iterable input list
- `expr` an expression which will be evaluated for each item

```
[1, 2, 3] | map (add . 2) // [3,4,5]
```

## length
Counts how many elements are in a iterable list. O(n) time, so use a property 
instead, if possible.

- `input` An iterable object

## join
Joins a list of elements together with a specified delimiter

- `input` an iterable list of elements that are convertible to a string
- `delimiter` The delimiter to use between elements

```
[1, 2, "hello"] | join "," // "1,2,hello"
```

## contains
Checks if a list has an element equal to the test value. Uses `cmp` internally
to compare values.

- `input` an iterable list of objects.
- `value` the test value

```
[1,2,3] | contains 2 // true
[1,2,3] | contains "yes" // false
```

## and
Performs a boolean (not bitwise) AND operation.

- `a` first value
- `b` second value

```
and true true // true
and true false // false
and false false // false
```

## or
Performs a boolean (not bitwise) OR operation.

- `a` first value
- `b` second value

```
and true true // true
and true false // true
and false false // false
```

## xor
Performs a boolean (not bitwise) XOR operation.

- `a` first value
- `b` second value

```
and true true // false
and true false // true
and false false // false
```

## not
Performs a boolean (not bitwise) NOT operation.

- `a` value

```
not true // false
not false // true
```

## rand
Generates a random number. `double` between 0 and 1 if no parameters. If 
parameters are specified, it will pick an integer in `[min, max]`.

- `min?` (Optional) minumum number
- `max?` (not optional if `min` is specified) maximum number

```
rand // 0.23587
rand 2 5 // 3
```

## randstr
Generates a random string of a specified length, from a key string. 

- `charset` the characters to pick from
- `length` the length of the generated string

```
randstr "123" 5 // 13223
randstr "abcdefghijklmnopqrstuvwxtz" 10 // mngkdospje
```

## add
Add two values. If one argument is a string, the other is converted to a 
string as well, and the are concatenated.

- `a` first value 
- `b` second value

```
add 2 5 // 7
add "2" 5 // "25"
```

## sub
Subtract two values.

- `a` first value 
- `b` second value

```
sub 3 5 // -2
sub 2.5 1.2 // 2.3
```

## mul
Multiply two values.

- `a` first value 
- `b` second value

```
mul 3 5 // 15
mul 2.5 2 // 5
```

## div
Divide two values. Always performs coercion to a `double`.

- `a` first value 
- `b` second value

```
sub 3 5 // 0.6
sub 12 4 // 3
```

## lt
Returns whether the first value is less than the second. Uses `cmp` internally.

- `a` first value
- `b` second value

```
lt 23 3 // false
lt 1.2 3 // true
lt 5 5 // false
```

## gt
Returns whether the first value is greater than the second. Uses `cmp` internally.

- `a` first value
- `b` second value

```
gt 23 3 // true
gt 1.2 3 // false
gt 5 5 // false
```

## eq
Returns whether the first value is equal to the second. Uses `cmp` internally.

- `a` first value
- `b` second value

```
eq 23 3 // false
eq 1.2 3 // true
eq 5 5 // true
```

## replace
Replaces all instances of a substring, with another string.

- `input` the input string
- `target` the substring to replace
- `value` the value to replace with

```
replace "hello" "l" "a" // "heaao"
replace "hello" "hello" "hi" // "hi"
replace "hello" "hello, world" "hi" // "hello"
```

## padEnd
Pad the end of the string with a character up to a certain length

- `input` the input string
- `length` the input string
- `padding` the input string, 1 character maximum

```
padEnd "123" 5 "0" // 12300
padEnd "hello" 10 " " // "hello     "
padEnd "hello" 3 "-" // "hello"
```

## padStart
Pad the start of the string with a character up to a certain length

- `input` the input string
- `length` the input string
- `padding` the input string, 1 character maximum

```
padEnd "123" 5 "0" // 00123
padEnd "hello" 10 " " // "     hello"
padEnd "hello" 3 "-" // "hello"
```

## trim
Trim leading and trailing whitespace from a string.

- `input` the input string

```
trim " hello   \t" // "hello"
trim "john" // "john"
```

## upper
Convert the string to all uppercase.

- `input` the input string

```
upper "hello" // "HELLO"
```

## lower
Convert the string to all lowercase.

- `input` the input string

```
upper "HELLO" // "hello"
```

## split
Split a string into a list, on a specified delimiter.

- `input` the input string
- `delimtier` the item delimiter

```
"1,2,3,4" // ["1","2","3","4"]
```

## substr
Get a substring from a string.

- `input` the input string
- `start` the start index (zero-based)
- `end?` (Optional) the end index (exclusive). Goes to end of string if not 
specified.

```
substr "Hello, World!" 0 5 // "Hello"
substr "Hello, World!" 5 // ", World!"
```
