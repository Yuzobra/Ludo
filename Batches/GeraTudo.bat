@ECHO  OFF
REM  Gera script de make de todos os exemplos teste manual

pushd  .

cd ..\Ferramentas

gmake /b..\Composicao /cTesteCasa /p..\Ferramentas\Gmake.parm
gmake /b..\Composicao /cTestePeca /p..\Ferramentas\Gmake.parm
gmake /b..\Composicao /cTesteLista /p..\Ferramentas\Gmake.parm
gmake /b..\Composicao /cTesteLisCirc /p..\Ferramentas\Gmake.parm
gmake /b..\Composicao /cTesteTabuleiro /p..\Ferramentas\Gmake.parm

popd
