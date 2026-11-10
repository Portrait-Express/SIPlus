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

## while (1.1.3)
Repeatedly evaluate the second parameter while the first parameter returns 
`true`. `condition` is evaulated, and while `condition` returns true, `expr` 
is evaluated. Returns the value that was returned from the last evaluation of 
`expr`.

- `condition` the condition, which shoudl return a truthy or falsy value
- `expr` the expression to evaulate each iteration

```
$i = 0; 
$str = "a";
while (lt $i 3) (
    $i = add $i 1;
    $str = add $str "a";
    0
);
$str // "aaaa"
```

## set_new (1.1.3)
Create a new instance of a set. This uses an internal implementation of a hash 
function to hash numeric and string values. Currently sets are not able to 
store non-string nor non-numeric values.

No arguments

```
set_new // a new set instance
```

## set_add (1.1.3)
Add an item to the set. Returns an instance to the set.

- `set` the set to modify
- `value` the value to add

```
set_new | set_add 123 // the set instance
```

## set_has (1.1.3)
Check if the set contains an item.

- `set` the set to modify
- `value` the value to check for

```
set_new | set_add 2 | set_has 3 // false
set_new | set_add 2 | set_has 2 // true
```

## type (2.0.1)
Get the type of the object (`TypeInfo::name()`)

- `data` The object to get the type of

```
2 | type // 'long'
2.3 | type // 'double'
null | type // 'null'
"test" | type // 'string'
```

## each (2.0.4)
Evaluate an expression for each instance in an array. Returns the result of the final evaluation.

- `list` The list to iterate
- `expr` The expression to evaluate

```
var $s = 0; [1, 2, 3] | each ($s = add $s .) // 6
```

## all (2.0.4)
Check if each item in a list matches a condition

- `list` The list to iterate
- `predicate` The condition expression

```
[true, true] | all // true
[true, false] | all // false
[false, false] | all // false
```

## any (2.0.4)
Check if any item in a list matches a condition

- `list` The list to iterate
- `predicate` The condition expression

```
[true, true] | all // true
[true, false] | all // true
[false, false] | all // false
```

## sort (2.0.4)
Create a new version of `list` sorted according to `comp`

- `list` The list to sort
- `[comp]` Comparator expression. This will be called with a default data 
containing a tuple of the first and second items to compare. If not specified,
will sort by using default Comparable implementation.

```
[2, 3, 1] | sort (sub .[0] .[1]) // [1, 2, 3]
```

## gte (2.2.0)
Greater than or equal to.

- `lhs` Left hand side
- `rhs` Right hand side

```
1 | gte 2 // false
2 | gte 2 // true
3 | gte 2 // true
```

## lte (2.2.0)
Less than or equal to.

- `lhs` Left hand side
- `rhs` Right hand side

```
1 | lte 2 // true
2 | lte 2 // true
3 | lte 2 // false
```

## find (2.2.0)
Search for an item in a list. Returns the first item matching `test`, or returns
null if `test` never returns `true`.

- `list` The list to search
- `test` Test expression

```
[2, 3, 1] | find (eq . 2) // 2
[2, 3, 1] | find (eq . 4) // null
```

## filter (2.2.0)
Create a new version of `list` filtered with `test`

- `list` The list to sort
- `test` Test expression

```
[2, 3, 1] | filter (. | gt 2) // [3]
[2, 3, 1] | filter (. | gt 2 | not) // [1, 2]
```

# Pair (2.3.0)

### Extensions:
- `Converter[string]`
- `Equatable`

A pair is a type that contains two other values. This can be used for keeping 
multiple data objects together when they are related.

### Properties:
- `first`: The first item in the pair
- `second`: The second item in the pair

```
pair "name" "John" | .first // "name"
pair "name" "John" | .second // "John"
```

## Functions

### pair 
Create a new pair instance

- `first` - The first item in the pair
- `second` - The second item in the pair
Returns: A new pair object

```
pair 1 "name" | str // { 1, name }
pair 1 2 | .second // 2
```


# Dictionary (2.3.0)

### Extensions:
- `Converter[string]`

A dictionary is the implementation of a hashmap, for those familiar with concept. In simple terms
it is a key-value map of information. You can use a dictionary to store any value to any key. The
keys types must be Hashable and Equatable.

A dictionary is iterable, and each item in the iterator is a `pair` object. When iterating a 
dictionary, the items are not guaranteed to be in any order. If you need to sort the elements,
consider creating a new array (for example with `dict_new | ... | map . | sort`).

```
dict_new | dict_set 1 "name" | dict_set 2 "id" | map (.first) // { 1, 2 }
```

You also may directly index a dictionary to get a value, although this will error if the value is 
not present in the dictionary. To look up a value that may not be present, use (dict_get)[#dict_get]

```
dict_new | dict_set 1 "test" | .[1] // "test"
```

## Functions

### dict_new
Create a new dictionary instance.

```
dict_new // New dictionary
```


### dict_set
Set a value in a dictionary. Returns the same dictionary instance.

- `dict` Dictionary instance
- `key` The key of the dictionary. This can be any Hashable and Equatable value type.
- `value` Dictionary value. This can be any value.

```
dict_new | dict_set "key" "value" | dict_set "other" "value2" 
// { { key, value }, { other, value2 } }
```


### dict_get
Get a value from a dictionary, or null, if the key does not exist.

- `dict` Dictionary instance
- `key` The key to look up

```
dict_new | dict_set "key" "value" | dict_get "key" // "value"
dict_new | dict_set "key" "value" | dict_get "key2" // null

// As opposed to
dict_new | dict_set "key" "value" | .["key2"] // throws error
```
