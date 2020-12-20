# Test Beam

_Minimal unit testing tool box written in C_

## About

### What is this

_Test Beam_ is a unit testing suite consisting of mostly C preprocessor 
macros for quick assertion-based unit tests. It is a single-file library 
consisting solely of the header file `beam.h` (see **Usage** for more 
information).

### Credits and Support

All content within this repository is released into the public domain 
([license 
text](https://github.com/ess3sq/test-beam/blob/master/LICENSE)). All 
kinds of use and redistribution are permitted, but no warranty is given, 
express or implied. As such, no support should be expected by the 
original author(s).

If you spot a bug or would like a feature to be added, you can open an 
Issue, however no kind of active support to this library should be 
expected.

If you wish to make changes you can issue a PR or redistribute a fork.

### To Do

Potential extensions to this toolbox that can be implemented in the future
are recorded in the file [`TODO.md`](https://github.com/ess3sq/test-beam/blob/master/TODO.md).

## Examples

Examples unit tests can be viewed in the [`examples/`](examples/) directory.

## Usage

## Inclusion

The library consists of a single short header file, containing mostly 
macros, as well as some `static` global constants and some functions.

While it contains header guards, the function definitions are provided 
instead of prototype declarations. As such, re-inclusion could be 
potentially problematic to compilers. What this means is, that this was 
this header is meant to be included only once throughout the entire 
project.

If that does not suit your needs, you might have to defer the 
implementations to a source file or (better) add yourself a separate 
implementation guard like this:

	#ifndef _BEAM_H
	#define _BEAM_H
	// ... move all macro definitions and forward declarations here
	

	#ifdef BEAM_IMPL
	// ... move function definitions here
	#endif

	#endif

This may require some thought about the `static` globals because they 
are used as memory storage for the test and assertion results. As such, 
it would be best to have them defined once only, not statically in every 
file that includes the header.

### Structure

The framework features 2 concepts: _Tests_ and _Assertions_. Assertions 
can either fail or pass, whereas tests can pass, fail or be skipped, the 
last result meaning that the test is neither successful nor insuccessful 
and as such should not be registered as either of them.

Assertions are supposed to be used to determine whether or not a test 
was successful or not, but this is not necessary: a test can be 
conducted in other ways since the criteria by which tests are judged 
successful or not is the user's business.

At the end of the tests, `B_SUMMARY()` ends the test suite and 
initializes a new test suite. It also outputs the number of assertions 
and tests that were conducted.

When a test or assertion is evaluated, _Test Beam_ logs the result to 
output.

### Interface

**1. External Access Functions**

The macro-functions intended for _external access_ are:

* `B_ASSERT(cond)` - performs assertion of the `bool` expression `cond` 
  and returns the `bool` value of the expression `cond`. This macro can 
  be used as if it were a true function call because its body actually 
  consists of a single function call (see `beam_assert`).

* `B_PASS()` - signals to _Test Beam_ that a test passed. This macro's 
  body consists of a multiple-statements body and cannot be used within 
  an expression, only as a stand-alone statement.

* `B_FAIL()` - signals to _Test Beam_ that a test failed (see `B_PASS()` 
  for more information).

* `B_SKIP()` - signals to _Test Beam_ that a test was skipped (see 
  `B_PASS()` for more information).

* `B_PASSm(s)` - essentially the same as `B_PASS()`, but allows for a 
  label to the test that is displayed in the log.

* `B_FAILm(s)` - essentially the same as `B_FAIL()`, but allows for a 
  label to the test that is displayed in the log.

* `B_SKIPm(s)` - essentially the same as `B_SKIP()`, but allows for a 
  label to the test that is displayed in the log.

* `B_SUMMARY()` - prints test and assertions summary to output and 
  resets the count.


**2. External Configuration Flags**

The behavior of these macro-functions can be customised by defining the 
following macros constants which serve as flags _before_ including the 
header (the value of the macro is _not_ used as a switch, only the state 
of defined/undefined is). As such, it is probably best to leave their 
values as undefined.

* `B_PASS_SILENTLY` - if defined, whenever a test passes, log output is 
  suppressed.

* `B_FAIL_SILENTLY` - if defined, whenever a test fails, log output is 
  suppressed.

* `B_SKIP_SILENTLY` - if defined, whenever a test is skipped, log output 
  is suppressed.

* `B_ASSERT_SILENTLY` - if defined, assertion evaluation is not logged.

* `B_KEEP_COUNT` - if defined, when the test suite is not closed when 
  `B_SUMMARY()` is called and subsequent tests and assertions are part 
  of the same suite. What this means is that only `B_SUMMARY()` only 
  logs the summary and does not reset the count.


* `B_SUMMARY_STR()` - expands to a string literal with format specifiers 
  which are meant to serve as placeholders for the test and assertion 
  count.


**3. Internal Functions**

The following macros are used in the implementation, which means they are
not intended to be used without the macro wrappers:

* `bool beam_assert(bool cond, char *str)` - asserts whether the `bool`
  value of `cond` and prints out `str` in parentheses. The `B_ASSERT(s)`
  macro passes `s` to `cond` and its stringification `#s` to `str`.
  
* `void beam_clear()` - clears count of all tests and assertions, provided
  the macro flag `B_KEEP_COUNT` is not set.
  
* `size_t beam_pass(const char *file, int line, const char *func, const char *msg)`
  - signals passing of test, is supposed to be used via the wrapper macro
    `PASS()` and `PASSm(s)`
    
* `size_t beam_fail(const char *file, int line, const char *func, const char *msg)`
  - signals failing of test, is supposed to be used via the wrapper macro
    `FAIL()` and `FAILm(s)`
    
* `size_t beam_skip(const char *file, int line, const char *func, const char *msg)`
  - signals failing of test, is supposed to be used via the wrapper macro
    `SKIP()` and `SKIPm(s)`
