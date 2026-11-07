# gpcp-JVM
Gardens Point Component Pascal compiler for the JVM

It is the JVM target of the excellent [GPCP compiler](https://github.com/k-john-gough/gpcp). After JDK 1.8.0_275 the JVM follows the spec more rigorously and does not allow semicolons in class names.

I've hacked the GPCP compiler to emit local/stack declarations without semicolons. It is now working on Java 11 and Java 17.

Good luck!

