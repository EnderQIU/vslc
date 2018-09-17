# Part I: VSL lexer analysis design

## VSL lexer definition

| Token | Definition（Regular Expression）                                                 |
| ------------- | ------------------------------------------------------------------ |
| identifier       | `[(FUNC)|(PRINT)|RETURN|CONTINUE|IF|THEN|ELSE|FI|WHILE|DO|DONE|VAR]` |
| assigner      | `:=`                                                             |
| operator      | `[+-*]`                                                             |
| delimiter     | `[\{\}\(\) \t\n]`                                                    |
| comment       | `"//".*`                                                             |
| variable      | `[A-Za-z]([A-Za-z]|[0-9])*`                                          |
| text          | `\”[A-Za-z]*\”`                                                      |
| integer       | `[1-9][0-9]*`                                                        |

## System design

Here contains three parts
1. logic: Logical part of laxer，include a DFA.
2. structure：Structure of laxer (a.k.a Token).
3. utils：Tools for the compiler, such as cmdline and source code reader package.

## DFA Ext-1 transformation graph

```ascii

+-+  isAlpha()  +-+   isDelimiter()|isSeparater()   +------------+
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
 |       isSeparater()        +-----------+                  |                       |
 +--------------------------->+d|Seperater|                  | +-> state transform   |
 |                            +-----------+                  |                       |
 |                                            !isLineBreak() | +-------------------+ |
 |       isOperator()         +-----------+    +---------+   | |x|a accepted state | |
 +--------------------------->+e|Operator |    |         |   | +-------------------+ |
 |                            +-----------+    |         |   +-----------------------+
 |                                             +---- <---+
 |        isSlash()           +-+    isSlash()     +-+   isLineBreak()    +----------+
 +--------------------------->+f+----------------->+g+------------------->+h|Comment |
 |                            +-+                  +-+                    +----------+
 |
 |        isDigit()           +-+   isSeparater()|isDelimiter()+----------+
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
See [test folder](test/)
