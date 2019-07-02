@ECHO  OFF
REM  Compila todos os Modulos de teste

pushd  .

cd ..\Ferramentas
nmake /F..\Composicao\TesteCasa.make "PRD="
nmake /F..\Composicao\TestePeca.make "PRD="
nmake /F..\Composicao\TesteLista.make "PRD="
nmake /F..\Composicao\TesteLisCirc.make "PRD="
nmake /F..\Composicao\TesteTabuleiro.make "PRD="
nmake /F..\Composicao\TestePartida.make "PRD="
nmake /F..\Composicao\Ludo.make "PRD="
del ..\Objetos\listacirc.obj
nmake /F..\Composicao\TesteLisCircCount.make
copy  ..\Err\*.err  ..\Err\tudo.err

popd
