JVM
===

This is a fully independent JVM implementation that can be either "hosted" by an
operating system, or "unhosted" without an operating system.

An "unhosted" demo for Sega Dreamcast was submitted as a part of the Dream Disc
'24 competition: https://purist.itch.io/dreamcast-jvm

Current status
--------------

The current JVM implementation is fairly complete, and will correctly interpret
a wide range of Java code correctly.

However, the following JVM features are not (yet) supported:

* invokedynamic (Java ≥9: Java lambdas, Java string concatenation, etc...)
* jsr/ret (Java ≤1.5: I have failed to independently reproduce the circumstances under which javac emits these instructions)
* synchronized methods (Java threads are also not implemented)
* runtime type checks (instanceof/checkedcast) on zero-length arrays of references
* interface fields
