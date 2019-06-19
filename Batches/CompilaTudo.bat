@ECHO  OFF
REM  Compila todos os Modulos de teste

pushd  .

cd ..\Ferramentas
nmake /F..\Composicao\TesteCasa.make "PRD="
nmake /F..\Composicao\TestePeca.make "PRD="
nmake /F..\Composicao\TesteLista.make "PRD="
nmake /F..\Composicao\TesteLisCirc.make "PRD="
nmake /F..\Composicao\TesteTabuleiro.make "PRD="

copy  ..\Err\*.err  ..\Err\tudo.err

popd
