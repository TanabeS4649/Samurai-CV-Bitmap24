rm image/output/*.bmp
ls -alh image/output/
cd src
make clean
make
cd ..
./bin/main image/input/samurai.bmp image/output/samurai.bmp
