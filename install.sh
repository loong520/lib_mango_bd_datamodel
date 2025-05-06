
#!/bin/bash
echo "cbb_home: $CBB_HOME"

version=1.0.0
echo "current library version: $version"

debug_path=$CBB_HOME/Mango/BlockDiagram/lib_mango_bd_datamodel/${version}/lib/linux/x64/debug
release_path=$CBB_HOME/Mango/BlockDiagram/lib_mango_bd_datamodel/${version}/lib/linux/x64/release

# copy debug library
if [ -d "$debug_path" ]; then
    cp -rf cmake-build-debug/libmangobddatamodel-${version}-d.so ${debug_path}
    if [ $? -eq 0 ]; then
        echo "succeed coping debug library to cbb directory"
    else
        echo "failed coping debug library to cbb directory"
    fi
else
    echo "The library directory does not exist: ${debug_path}"
fi

# copy release library
if [ -d "$release_path" ]; then
    cp -rf cmake-build-release/libmangobddatamodel-${version}.so ${release_path}
    if [ $? -eq 0 ]; then
        echo "succeed coping release library to cbb directory"
    else
        echo "failed coping release library to cbb directory"
    fi
else
    echo "The library directory does not exist: ${release_path}"
fi
