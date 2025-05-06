
echo "build debug......"
debug_dir=cmake-build-debug
if [ ! -d "$debug_dir" ]; then
   mkdir $debug_dir
fi
cd $debug_dir
rm cmake* -fr
rm CMake* -fr
cmake -DCMAKE_BUILD_TYPE=Debug -S .. -B .
make -j10
cd ..

echo "build release......"
release_dir=cmake-build-release
if [ ! -d "$release_dir" ]; then
   mkdir $release_dir
fi
cd $release_dir
rm cmake* -fr
rm CMake* -fr
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
make -j10
cd ..
