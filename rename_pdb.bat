setlocal enableextensions enabledelayedexpansion

@echo off 
for /r "C:\Stephane\Enseignement\Polytechnique\2016-2017\INF473S\Git\INF473S-X15\PDB_RENAME\" %%X in (*.ent) do (
For %%A in ("%%X") do (
	set Name=%%~nA
	set Name=!Name:~3!
	call :ToUpcaseWithFor "!Name!" Name
	echo !Name!
  
  
	
	Ren "%%X" "!Name!.pdb"
	move "!Name!.pdb" ..\PDB_EXTR\
	
)
)

endlocal & goto :EOF

:ToUpcaseWithFor
  set var_=%~1
  for %%c in (1 2 3 4 5 6 7 8 9 0 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
    set var_=!var_:%%c=%%c!
    )
  endlocal & set %2=%var_%& goto :EOF
