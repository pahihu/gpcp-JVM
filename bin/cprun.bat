@echo off
REM run the class file
java -DCPSYM=.;%JRoot%\symfiles;%JRoot%\symfiles\JvmSystem -cp .;%JRoot%\libs CP.%1.%1 %2 %3 %4 %5 %6 %7 %8 %9
