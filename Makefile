

parametrosCompilacao=-Wall 
nomePrograma=myavl

all: $(nomePrograma)

$(nomePrograma): 
	gcc main.c avl.c -o $(nomePrograma) $(parametrosCompilacao)

clean:
	rm -f $(nomePrograma)
	rm -f *.o *.gch
