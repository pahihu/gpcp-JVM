@echo off
java -DCPSYM=.;%JRoot%\symfiles;%JRoot%\symfiles\JvmSystem -jar %JRoot%\jars\cpmake.jar %1 %2 %3 %4 %5 %6 %7 %8 %9

