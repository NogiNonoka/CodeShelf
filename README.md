# CodeShelf

A code shelf for XCPC Template.

Author: NogiNonoka

Data: 2020 - 11 - 09

## C++ CodeStyleGuide

### Files

- Name as `$AlgorithmName.h` or `$AlgorithmName.cpp`

- If you use a Header Files, Submit a `($AlgorithmName)_Test.cpp` for test.

### Header

- Permit but Not Recommend using `bits/stdc++.h`;

- Do **Not** Use `#define` for Constants, using `const` instead;

- Do **Not** Use `typedef` for Variable Types, using `template<typename >` or just use `int` and `double`;

### Comments

- Use `//` or `/* */`;

#### Struct / Template Comments:

- Other Algorithms you Used in your Algorithm;

- Analyze Time and Space Complexity;

#### Functions / Variables Comments:

- Optional

- Use `//` in a Single Line;

### Algorithm

- Recommend using **Struct / Template** for Data Structure and Algorithm;

- Use **Pascal Case** for Naming Functions in Struct;

- Add a **DEBUG** part / function;

- (Optional) Add a **Problem ID** with a **Link** and solve it in your `main` function or **Independent** `solve` function;

### Constant

```C++
// Optional
#define int long long 
#define double long double
const int MAXN = ;
const int MOD = ;
const int INF = ;
const double eps = ;
const double PI = acos(-1);
const int DIRX[] = {};
const int DIRY[] = {};
```

This Constants which you Use should be defined in your Template;

## Catalogue

**CodeShelf**
├─DataStructure

├─DynamicPrograming

├─GraphTheory

├─MathTheory

├─Others

└─String
