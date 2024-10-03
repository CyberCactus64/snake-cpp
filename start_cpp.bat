@echo off

echo Compilazione iniziata...
g++ main.cpp -o main.exe

:: Verifica se la compilazione è andata a buon fine
if %ERRORLEVEL% neq 0 (
    echo Errore nella compilazione.
    exit /b %ERRORLEVEL%
)

echo Esecuzione codice...
main.exe

:: Verifica se l'esecuzione è andata a buon fine
if %ERRORLEVEL% neq 0 (
    echo Errore durante l'esecuzione del programma.
    exit /b %ERRORLEVEL%
)