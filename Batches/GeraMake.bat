@ECHO  OFF
REM  Gera script de make
REM    Sintaxe   GeraMake Ludo.comp

pushd  .

if ""=="%1" goto erro

cd ..\Composicao
gmake /c%1  /b..\Composicao
goto sai

:erro
echo Falta nome do arquivo de diretivas de composicao

:sai
popd
