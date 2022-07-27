# ADB in action
# Explicit Mode
Explicit mode is a feature of ADB that allows the user to understand and inspect
Asteroid's pattern matching. Pattern matching in Asteroid is generally silent,
meaning you only really see the details of it when an error occurs. Explicit mode,
however, allows you to see every mattern matching operation that Asteroid carries
out.

>> Rewrite this
It is reccomended to step through functions to the specific line you are interested
in while in explicit mode as opposed to over them as going over a function in explicit 
mode (using the `next` command) can produce output that may be overly long and
difficult to read.

Let's take a look at a debugging session on a program that uses first-class 
patterns to enforce a type:

We see the simple 4 line program. We have a pattern that is essentially the
range (0,10) and two variable declarations with typematches.
```
[/home/user/example1.ast (1)]
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

Here we see explicit mode being enabled using the `e` command 
and a simple typematch
occuring. We can see the constraint-only pattern, the internal
condition, the internal variable `x` being unified, the
condition being met, and finally `z` being set to 9 as 9 succeeded
the typematch.

During unification, explicit mode shows the user the exact
term and pattern which will be matched. Seen as `** pattern:` and
`** term:`.

```
[/home/user/example1.ast (3)]
-->> let z:*p = 9.
(ADB) e
(ADB)[e] n
 ** pattern: z:*p
 ** term: 9
- Matching term z to pattern *p
|   - Dereferencing p
|    ** *p -> %[x:%integer if (condition...)]%
|   - [Begin] constraint pattern: x:%integer if (condition...)
|   |   - Conditional match: if (x > 0 and x < 10)
|   |   |   - Matching term x to pattern %integer
|   |   |   |   - Typematch 9 to type integer
|   |   |   |    ** Success!
|   |   |   - Matched!
|   |   |   - x = 9
|   |   - Condition met, x > 0 and x < 10
|   - [End] constraint pattern
- Matched!
- z = 9
[/home/user/example1.ast (4)]
-->> let y:*p = 11.
(ADB)[e] n
```

Here we see something similar. We can see the constraint-only
pattern, the typematch to integer, but, when we get to the conditional
part of the pattern, we see a failure. With explicit mode, we can see
exactly *where* in the pattern the failure occurs.
```
[/home/user/example1.ast (4)]
-->> let y:*p = 11.
(ADB)[e] n
 ** pattern: y:*p
 ** term: 11
- Matching term y to pattern *p
|   - Dereferencing p
|    ** *p -> %[x:%integer if (condition...)]%
|   - [Begin] constraint pattern: x:%integer if (condition...)
|   |   - Conditional match: if (x > 0 and x < 10)
|   |   |   - Matching term x to pattern %integer
|   |   |   |   - Typematch 11 to type integer
|   |   |   |    ** Success!
|   |   |   - Matched!
|   |   |   - x = 11
|   |   - Condition (x > 0 and x < 10) failed

ERROR: /home/user/example1.ast: 4: pattern match failed: conditional pattern match failed
    ==>> let y:*p = 11.

----- Error occured, session will restart after commands -----
[/home/user/example1.ast (4)]
-->> let y:*p = 11.
(ADB)[e] 
```

## Another example
Here we have a simple program with one major assert which will help us demonstrate how we can
read the explicit mode information to decipher failed pattern matches.

We have two patterns, `p` and `d`. `d` is composed of three `p`'s. `p` is the range of numbers
(0,100).

In the assert, we see that we are trying to match a tuple of two numbers and a string against `d`.
By the definition of `d` we can see that this will fail. But, let this be a proxy for a more
complicated example. Let's investigate exactly *why* this pattern match fails.

```
[/home/user/example2.ast (1)]
-->> let p = pattern %[(x:%integer) if x > 0 and x < 100]%.
(ADB) ll
----- Program Listing -----
>  1 let p = pattern %[(x:%integer) if x > 0 and x < 100]%.
   2 let d = pattern %[(a:*p, b:*p, c:*p)]%.
   3 
   4 assert(not ((1,2,"A") is *d)).
   5 [EOF]
(ADB) s
[/home/user/example2.ast (2)]
-->> let d = pattern %[(a:*p, b:*p, c:*p)]%.
(ADB) s
```

By following the tab leveling and pattern tree, we can see the exact point where the pattern match fails.

We see that within the first constraint pattern, on the last item in the tuple, we have a failed
typematch. This makes sense as `d` is composed of three `p`'s. All of which are integers.

```
[/home/user/example2.ast (4)]
-->> assert(not ((1,2,"A") is *d)).
(ADB) e
(ADB)[e] n
- Asserting: not ((1,2,A) is *d)
|   - Dereferencing d
|    ** *d -> %[(a:*p,b:*p,c:*p)]%
|   - [Begin] constraint pattern: (a:*p,b:*p,c:*p)
|   |   - Matching lists: [a:*p,b:*p,c:*p] and [1,2,A]
|   |   |   - Matching term a to pattern *p
|   |   |   |   - Dereferencing p
|   |   |   |    ** *p -> %[x:%integer if (condition...)]%
|   |   |   |   - [Begin] constraint pattern: x:%integer if (condition...)
|   |   |   |   |   - Conditional match: if (x > 0 and x < 100)
|   |   |   |   |   |   - Matching term x to pattern %integer
|   |   |   |   |   |   |   - Typematch 1 to type integer
|   |   |   |   |   |   |    ** Success!
|   |   |   |   |   |   - Matched!
|   |   |   |   |   |   - x = 1
|   |   |   |   |   - Condition met, x > 0 and x < 100
|   |   |   |   - [End] constraint pattern
|   |   |   - Matched!
|   |   |   - Matching term b to pattern *p
|   |   |   |   - Dereferencing p
|   |   |   |    ** *p -> %[x:%integer if (condition...)]%
|   |   |   |   - [Begin] constraint pattern: x:%integer if (condition...)
|   |   |   |   |   - Conditional match: if (x > 0 and x < 100)
|   |   |   |   |   |   - Matching term x to pattern %integer
|   |   |   |   |   |   |   - Typematch 2 to type integer
|   |   |   |   |   |   |    ** Success!
|   |   |   |   |   |   - Matched!
|   |   |   |   |   |   - x = 2
|   |   |   |   |   - Condition met, x > 0 and x < 100
|   |   |   |   - [End] constraint pattern
|   |   |   - Matched!
|   |   |   - Matching term c to pattern *p
|   |   |   |   - Dereferencing p
|   |   |   |    ** *p -> %[x:%integer if (condition...)]%
|   |   |   |   - [Begin] constraint pattern: x:%integer if (condition...)
|   |   |   |   |   - Conditional match: if (x > 0 and x < 100)
|   |   |   |   |   |   - Matching term x to pattern %integer
|   |   |   |   |   |   |   - Typematch A to type integer
|   |   |   |   |   |   |    ** Failure
- Assert Succeeded
[/home/user/example2.ast (5)]
-->> [EOF]
(ADB)[e] 
```