REM executa os testes dos modulos criados


if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Exe\testeCasa /s..\Scripts\TesteCasa    /l..\Exe\TesteCasa   /a..\Scripts\estatisticas
..\Exe\testePeca /s..\Scripts\TestePeca    /l..\Exe\TestePeca   /a..\Scripts\estatisticas
..\Exe\testeLista /s..\Scripts\TesteLista    /l..\Exe\TesteLista   /a..\Scripts\estatisticas
..\Exe\testeLisCirc /s..\Scripts\TesteLisCirc    /l..\Exe\TesteLisCirc   /a..\Scripts\estatisticas
..\Exe\testeTabuleiro /s..\Scripts\TesteTabuleiro /l..\Exe\TesteTabuleiro /a..\Scripts\estatisticas

..\Ferramentas\exbestat /e..\Scripts\estatisticas
