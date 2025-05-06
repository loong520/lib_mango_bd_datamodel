echo %CBB_HOME%

xcopy /E /I /Y .\include\* %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\include\

xcopy /Y .\cmake-build-debug\libmangobddatamodel-1.0.0-d.dll %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\lib\win\debug\
xcopy /Y .\cmake-build-debug\libmangobddatamodel-1.0.0-d.lib %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\lib\win\debug\
xcopy /Y .\cmake-build-debug\libmangobddatamodel-1.0.0-d.pdb %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\lib\win\debug\

xcopy /Y .\cmake-build-release\libmangobddatamodel-1.0.0.dll %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\lib\win\release\
xcopy /Y .\cmake-build-release\libmangobddatamodel-1.0.0.lib %CBB_HOME%\Mango\BlockDiagram\lib_mango_bd_datamodel\1.0.0\lib\win\release\