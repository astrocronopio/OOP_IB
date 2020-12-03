#Me hice el script para hacer el linking. 
#Por si tienen linux: Se corre usando --- $ bash linking.sh  ---

g++ -c ejer_10_archivo_1.cpp 
g++ -c ejer_10_archivo_2.cpp 
g++ -o ejer_10 ejer_10_archivo_1.o ejer_10_archivo_2.o
./ejer_10