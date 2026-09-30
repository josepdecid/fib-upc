OPTIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Product.o Customer.o Cjt_Customers.o Optimus.o
	g++ -o program.exe Product.o Customer.o Cjt_Customers.o Optimus.o program.o
	rm *.o

program.o:
	g++ -c program.cc $(OPTIONS)

Optimus.o:
	g++ -c Optimus.cc $(OPTIONS)

Cjt_Customers.o:
	g++ -c Cjt_Customers.cc $(OPTIONS)

Customer.o:
	g++ -c Customer.cc $(OPTIONS)

Product.o:
	g++ -c Product.cc $(OPTIONS)

DoxygenDOC:
	doxygen Doxyfile

htmlzipped:
	zip -r html.zip DOC/html
	rm -r DOC

practica.tar: DoxygenDOC htmlzipped
	tar -cvf practica.tar program.cc Product.* Customer.* Cjt_Customers.* Optimus.* Makefile jp_*.txt html.zip equip.pdf
	rm html.zip

clean:
	rm *.o
	rm *.exe
	rm *.gch
