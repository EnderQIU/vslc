# Part I: VSL Lexical Analysis Design

## VSL lexer definition

| Token | Definition（Regular Expression）                                            |
| ------------ | ------------------------------------------------------------------   |
| identifier   | `[(FUNC)|(PRINT)|RETURN|CONTINUE|IF|THEN|ELSE|FI|WHILE|DO|DONE|VAR]` |
| assigner     | `:=`                                                                 |
| operator     | `[+-*]`                                                              |
| delimiter    | `[\{\}\(\) \t\n]`                                                    |
| separator    | `[{}(),]`                                                            |
| comment      | `"//".*`                                                             |
| variable     | `[A-Za-z]([A-Za-z]|[0-9])*`                                          |
| text         | `\”[A-Za-z0-9/w]*\”`                                                 |
| integer      | `[1-9][0-9]*`                                                        |

## System design

Here contains three parts
1. logic: Logical part of laxer，include a DFA.
2. structure：Structure of laxer (a.k.a Token).
3. utils：Tools for the compiler, such as cmdline and source code reader package.

## DFA Ext-1 transformation graph

```ascii

+-+  isAlpha()  +-+   isDelimiter()|isSeparator()   +------------+
|s+------------>+a+-------------------------------->+b|Identifier|
+++             +-+   |isOperator()|isColon()       +------------+
 |        +----- <------+
 |        |             |        isColon()      +-+  isEqualSign()  +----------+
 |        |             |  +------------------->+m+---------------->+n|Assigner|
 |        |  isAlpha()  |  |                    +-+                 +----------+
 |        +-------------+  |
 |           isDigit()     |                                 +-----------------------+
 +-------------------------+                                 | Example:              |
 |       isDelimiter()        +-----------+                  |                       |
 +--------------------------->+c|Delimiter|                  | +-+                   |
 |                            +-----------+                  | | | a unaccepted state|
 |                                                           | +-+                   |
 |       isSeparator()        +-----------+                  |                       |
 +--------------------------->+d|Separator|                  | +-> state transform   |
 |                            +-----------+                  |                       |
 |                                            !isLineBreak() | +-------------------+ |
 |       isOperator()         +-----------+    +---------+   | |x|a accepted state | |
 +--------------------------->+e|Operator |    |         |   | +-------------------+ |
 |                            +^----------+    |         |   +-----------------------+
 |                  !isSlash() |               +---- <---+
 |        isSlash()           +-+    isSlash()     +-+   isLineBreak()    +----------+
 +--------------------------->+f+----------------->+g+------------------->+h|Comment |
 |                            +-+                  +-+                    +----------+
 |
 |        isDigit()           +-+   isSeparator()|isDelimiter()+----------+
 +--------------------------->+i+----------------------------->+j|Integer |
 |                            +-+   |isOperator()|isColon()    +----------+
 |                         +--+ <--+
 |                         |       |
 |                         |       |
 |                         +-------+
 |                         isDigit()
 |
 |        isQuotationMark()          +-+      isQuotationMark()     +--------+
 +---------------------------------->+k+--------------------------->+l|Text  |
                                     +-+                            +--------+

```

## Test case and result
```bash
> vslc/cmake-build-debug/vslc -v test.vsl
====================================
Lexical Analysis Result Table         
====================================
Line   Column Token         Value               
------------------------------------
1      1      FUNC          FUNC                
1      5      DELIMITER     /w                  
1      6      IDENTIFIER    main                
1      10     L_BRACKET     (                   
1      11     R_BRACKET     )                   
1      12     DELIMITER     \n                  
2      1      L_CURLY_BRACE {                   
2      2      DELIMITER     \n                  
3      1      DELIMITER     /w                  
3      2      DELIMITER     /w                  
3      3      DELIMITER     /w                  
3      4      DELIMITER     /w                  
3      5      COMMENT       // This is a comment
3      25     DELIMITER     \n                  
4      1      DELIMITER     \t                  
4      2      VAR           VAR                 
4      5      DELIMITER     /w                  
4      6      IDENTIFIER    i                   
4      7      DELIMITER     \n                  
5      1      DELIMITER     \t                  
5      2      IDENTIFIER    i                   
5      3      DELIMITER     /w                  
5      4      ASSIGN        :=                  
5      6      DELIMITER     /w                  
5      7      INTEGER       0                   
5      8      DELIMITER     \n                  
6      1      DELIMITER     \t                  
6      2      VAR           VAR                 
6      5      DELIMITER     /w                  
6      6      IDENTIFIER    a                   
6      7      COMMA         ,                   
6      8      DELIMITER     /w                  
6      9      IDENTIFIER    b                   
6      10     COMMA         ,                   
6      11     DELIMITER     /w                  
6      12     IDENTIFIER    c                   
6      13     DELIMITER     \n                  
7      1      DELIMITER     \t                  
7      2      IDENTIFIER    a                   
7      3      DELIMITER     /w                  
7      4      ASSIGN        :=                  
7      6      DELIMITER     /w                  
7      7      INTEGER       8                   
7      8      DELIMITER     \n                  
8      1      DELIMITER     \t                  
8      2      IDENTIFIER    b                   
8      3      DELIMITER     /w                  
8      4      ASSIGN        :=                  
8      6      DELIMITER     /w                  
8      7      INTEGER       2                   
8      8      DELIMITER     \n                  
9      1      DELIMITER     \t                  
9      2      IDENTIFIER    c                   
9      3      DELIMITER     /w                  
9      4      ASSIGN        :=                  
9      6      DELIMITER     /w                  
9      7      IDENTIFIER    a                   
9      8      DELIMITER     /w                  
9      9      DIVIDE        /                   
9      10     DELIMITER     /w                  
9      11     IDENTIFIER    b                   
9      12     DELIMITER     \n                  
10     1      DELIMITER     /w                  
10     2      DELIMITER     /w                  
10     3      DELIMITER     /w                  
10     4      DELIMITER     /w                  
10     5      WHILE         WHILE               
10     10     DELIMITER     /w                  
10     11     INTEGER       11                  
10     13     DELIMITER     /w                  
10     14     MINUS         -                   
10     15     DELIMITER     /w                  
10     16     IDENTIFIER    i                   
10     17     DELIMITER     \n                  
11     1      DELIMITER     \t                  
11     2      DO            DO                  
11     4      DELIMITER     \n                  
12     1      DELIMITER     \t                  
12     2      L_CURLY_BRACE {                   
12     3      DELIMITER     \n                  
13     1      DELIMITER     \t                  
13     2      DELIMITER     \t                  
13     3      PRINT         PRINT               
13     8      DELIMITER     /w                  
13     9      TEXT          "f( "               
13     14     COMMA         ,                   
13     15     DELIMITER     /w                  
13     16     IDENTIFIER    i                   
13     17     COMMA         ,                   
13     18     DELIMITER     /w                  
13     19     TEXT          " ) = "             
13     26     COMMA         ,                   
13     27     DELIMITER     /w                  
13     28     IDENTIFIER    f                   
13     29     L_BRACKET     (                   
13     30     IDENTIFIER    i                   
13     31     R_BRACKET     )                   
13     32     COMMA         ,                   
13     33     DELIMITER     /w                  
13     34     DELIMITER     /w                  
13     35     TEXT          "\n"                
13     39     DELIMITER     \n                  
14     1      DELIMITER     \t                  
14     2      DELIMITER     \t                  
14     3      IDENTIFIER    i                   
14     4      DELIMITER     /w                  
14     5      ASSIGN        :=                  
14     7      DELIMITER     /w                  
14     8      IDENTIFIER    i                   
14     9      DELIMITER     /w                  
14     10     PLUS          +                   
14     11     DELIMITER     /w                  
14     12     INTEGER       1                   
14     13     DELIMITER     \n                  
15     1      DELIMITER     \t                  
15     2      R_CURLY_BRACE }                   
15     3      DELIMITER     \n                  
16     1      DELIMITER     \t                  
16     2      DONE          DONE                
16     6      DELIMITER     \n                  
17     1      R_CURLY_BRACE }                   
17     2      DELIMITER     \n                  
18     1      FUNC          FUNC                
18     5      DELIMITER     /w                  
18     6      IDENTIFIER    f                   
18     7      L_BRACKET     (                   
18     8      IDENTIFIER    n                   
18     9      R_BRACKET     )                   
18     10     DELIMITER     \n                  
19     1      L_CURLY_BRACE {                   
19     2      DELIMITER     \n                  
20     1      DELIMITER     \t                  
20     2      IF            IF                  
20     4      DELIMITER     /w                  
20     5      IDENTIFIER    n                   
20     6      DELIMITER     \n                  
21     1      DELIMITER     \t                  
21     2      THEN          THEN                
21     6      DELIMITER     \n                  
22     1      DELIMITER     \t                  
22     2      DELIMITER     \t                  
22     3      RETURN        RETURN              
22     9      DELIMITER     /w                  
22     10     IDENTIFIER    n                   
22     11     DELIMITER     /w                  
22     12     MULTIPLY      *                   
22     13     DELIMITER     /w                  
22     14     IDENTIFIER    f                   
22     15     L_BRACKET     (                   
22     16     IDENTIFIER    n                   
22     17     DELIMITER     /w                  
22     18     MINUS         -                   
22     19     DELIMITER     /w                  
22     20     INTEGER       1                   
22     21     R_BRACKET     )                   
22     22     DELIMITER     \n                  
23     1      DELIMITER     \t                  
23     2      ELSE          ELSE                
23     6      DELIMITER     \n                  
24     1      DELIMITER     \t                  
24     2      DELIMITER     \t                  
24     3      RETURN        RETURN              
24     9      DELIMITER     /w                  
24     10     INTEGER       1                   
24     11     DELIMITER     \n                  
25     1      DELIMITER     \t                  
25     2      FI            FI                  
25     4      DELIMITER     \n                  
26     1      R_CURLY_BRACE }                   
------------------------------------

Process finished with exit code 0
```
