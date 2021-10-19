CFLAGS=-std=c99 -fstack-protector-all -g

t1:
	gcc $(CFLAGS) -c quadra.c -o quadra.o 
	gcc $(CFLAGS) -c listaDup.c -o listaDup.o
	gcc $(CFLAGS) -c path.c -o path.o 
	gcc $(CFLAGS) -c svg.c -o svg.o 
	gcc $(CFLAGS) -c qry.c -o qry.o 
	gcc $(CFLAGS) -c txt.c -o txt.o 
	gcc $(CFLAGS) -c lerArquivoQry.c -o lerArquivoQry.o 
	gcc $(CFLAGS) -c lerArquivoPm.c -o lerArquivoPm.o 
	gcc $(CFLAGS) -c lerArquivoGeo.c -o lerArquivoGeo.o 
	gcc $(CFLAGS) -c arvoreAvl.c -o arvoreAvl.o 
	gcc $(CFLAGS) -c tabelaEspalhamento.c -o tabelaEspalhamento.o
	gcc $(CFLAGS) -c moradia.c -o moradia.o
	gcc $(CFLAGS) -c pessoa.c -o pessoa.o
	gcc $(CFLAGS) -c locacao.c -o locacao.o  
	gcc $(CFLAGS) main.c quadra.o listaDup.o path.o svg.o qry.o txt.o lerArquivoQry.o lerArquivoPm.o lerArquivoGeo.o arvoreAvl.o tabelaEspalhamento.o moradia.o pessoa.o locacao.o -g -lm -o t1 $(CFLAGS)

clean:
	rm *.o
	rm t1