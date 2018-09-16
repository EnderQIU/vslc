# Part I: VSL lexer analysis design

## VSL lexer definition

| Token | Definition（Regular Expression）                                                 |
| ------------- | ------------------------------------------------------------------ |
| identifier       | `[(FUNC)|(PRINT)|RETURN|CONTINUE|IF|THEN|ELSE|FI|WHILE|DO|DONE|VAR]` |
| operator      | `[+-*/]`                                                             |
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

## Test case and result
See [test folder](test/)
