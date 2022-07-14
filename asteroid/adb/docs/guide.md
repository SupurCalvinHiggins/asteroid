# Quick Start
The Asteroid Debugger (ADB) is a source code debugger for the Asteroid programming language.

It supports the following:
* Breakpoints
* Single stepping at the source level
* Stepping through function calls
* Stack frame inspection
* Evaluation of arbitrary Asteroid code
* Macros
* REPL Instances

ADB features an "explicit" mode which details much of the pattern matching and underlying
mechanics of Asteroid to give developers a better idea of what's going on. Explicit mode
details many of the steps of pattern matching, function calling, statement execution, and
return values.

## Usage
`TDB`

## Commands
Below is a list of the commands available to the debugger. Most of which can be shortened.
These shortenings are shown in parenthesis (`c(ommand)`).

### Step
`s(tep)` through to the next statement or through function call.

### Continue
`c(ontinue) cont(inue)` continue execution until the next breakpoint.

### Next
`n(ext)` continue onto the next executing line at the current scope.

### Break
`b(reak) (number)*` set a breakpoint at one or more lines. Running without any arguments
lists your breakpoints.

Example: `b 1 2 3`, `break`.

### Delete
`d(elete) (number)+` `del(ete) (number)+` delete a list of breakpoints.

### Macro
`macro (name) (command list)`. Define a macro. Running just `macro` lists your macros.

Example macro that continues to a breakpoint and prints the value of x:
```
macro gox = c; eval("io@println(x)");
```

### Eval
`eval("asteroid code")` Evaluate the asteroid code between quotes. Works exactly like a single-line
repl.

Example, print out the value of `x`:
```
eval("x")
```

### !
`!` Open up a repl in the current context

### Help
`h(elp) (command)?` gives help for a given command. Running just `help` shows all available commands.
Example:
```
h macro
help break
```

### < (Up)
`<` move up one stack frame

### > (Down)
`>` move down one stack frame

### Where
`w(here)` displays the frame stack and the currently active frame.

### Longlist
`ll (longlist)` lists the entire program

### List
`l(ist)` lists the lines around the currently executing line

### Explicit
`e(xplicit) (on|off)?` By default, this command run without an argument toggles
explicit mode. If given a literal `on` or `off`, explicit mode will be switched
to the corresponding state.

# Explicit Mode
Explicit mode is a feature of ADB that allows the user to understand and inspect
Asteroid's pattern matching.

Let's take a look at a debugging session on a program that uses first-class 
patterns to enforce a type:

We see the simple 4 line program. We have a pattern that is essentially the
range (0,10) and two variable declarations with typematches.
```
[/home/oliver/example2.ast (1)]
-->> let p = pattern %[(x:%integer) if x > 0 and x < 10]%.
(ADB) ll
----- Program Listing -----
>  1 let p = pattern %[(x:%integer) if x > 0 and x < 10]%.
   2 
   3 let z:*p = 9.
   4 let y:*p = 11.
   5 [EOF]
(ADB) n
```

Here we see explicit mode being enabled and a simple typematch
occuring. We can see the constraint-only pattern, the internal
condition, the internal variable `x` being unified, the
condition being met, and finally `z` being set to 9 as 9 succeeded
the typematch.
```
[/home/oliver/example2.ast (3)]
-->> let z:*p = 9.
(ADB) e
(ADB)[e] n
 ** pattern: z:*p
 ** term: 9
- Matching term z to pattern *p
- Dereferencing p
 ** *p -> %[x:%integer if (condition...)]%
- [Begin] constraint pattern
  - Conditional match: if (x > 0 and x < 10)
    - Matching term x to pattern %integer
    - Typematch 9 to type integer
     ** Success!
    - x = 9, 
  - Condition met, x > 0 and x < 10
- [End] constraint pattern
- z = 9
```

Here we see something similar. We can see the constraint-only
pattern, the typematch to integer, but, when we get to the conditional
part of the pattern, we see a failure. With explicit mode, we can see
exactly *where* in the pattern the failure occurs.
```
[/home/oliver/example2.ast (4)]
-->> let y:*p = 11.
(ADB)[e] n
 ** pattern: y:*p
 ** term: 11
- Matching term y to pattern *p
- Dereferencing p
 ** *p -> %[x:%integer if (condition...)]%
- [Begin] constraint pattern
  - Conditional match: if (x > 0 and x < 10)
    - Matching term x to pattern %integer
    - Typematch 11 to type integer
     ** Success!
    - x = 11, 
    - Condition (x > 0 and x < 10) failed

ERROR: /home/oliver/example2.ast: 4: pattern match failed: conditional pattern match failed
    ==>> let y:*p = 11.

----- Error occured, session will restart after commands -----
[/home/oliver/example2.ast (4)]
-->> let y:*p = 11.
(ADB)[e] 
```

---

# Developer's guide
When trying to integrate the debugger's functionality into new asteroid code, a developer really only
needs to understand the core functions that allow 99% of the debugger to work within `walk`.

## notify_debugger

## message_explicit
`message_explicit` `gen_t2s`

## Tab leveling
### increase_debugger_tab_level

### decrease_debugger_tab_level