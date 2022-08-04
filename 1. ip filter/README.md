## The Condition

The program reads data from stdin.
The data is stored line by line.
All the lines are consisted of 3 fields separated by `\t` symbol and end with a `\n` symbol.

`text1 \t text2 \t text3 \n`

Fields `text2` and `text3` must be ignored and field `text1` is an ipv4 address string like `n1.n2.n3.n4` where `nX` is a number 0-255.

## The Task

1. Load IP addresses from stdin.

2. Output addresses in the following order (address per line):
   
   1. All addresses in reverse lexicographical order
   
   2. All addresses with `n1 = 1`, same sorting order.
   
   3. All addresses with `n1 = 46, n2 = 70`, same sorting order.
   
   4. All addresses which *any byte* equals 46, same sorting order.

3. Use C++ 14 features where it's possible.

## Scores

| score | condition                                                 |
|:-----:|:--------------------------------------------------------- |
| 5     | Program works correctly                                   |
| 2     | Log(n) complexity of one of the filters                   |
| 1     | Sorting without custom comparators                        |
| 2     | There are no custom std::any_of, std::equal, std::copy_if |
| 1     | There are `using` synonyms                                |
| 2     | One of the filters is a variadic template                 |
| 2     | Filters are lambda functions                              |
| 2     | There are tests for the task                              |
| 1     | No one compiler warnings                                  |
