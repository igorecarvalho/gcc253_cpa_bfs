 
# Trabalho 01 - Utilização da estrutura de dados “bags” na busca em largura
- Este repositório contêm a solução para a trabalho 01 da disciplina de GCC253-CPA-UFLA.


## Uma breve descrição
 - Neste trabalho, apresentaremos um algoritmo de busca em largura em grafos com utilização de uma estrutura nomeada de BAGS. Uma Bag é uma estrutura de dados que aceita itens duplicados, não ordenados e são armazenados como árvores binárias perfeitas. Representamos uma Bag S usando um tamanho fixo de vetor S[0..r]chamado de backbone, onde 2r+1 excede o número máximo de elementos já armazenados em uma Bag. Cada entrada S[k] no backbone contém um ponteiro nulo ou um ponteiro para uma Pennant do tamanho 2k[3].

## Para executar:
- no terminal use:
- ```git clone https://github.com/igorecarvalho/gcc253_cpa_bfs```;
- use ```make``` para compilar os arquivos;
- as instâncias estão armazenadas dentro do diretorio ```instences```
- para execução do código utiliza a seguinte linha de comando no terminal: ```./main <num_vertices> <edges_filename>```
- - onde:
- - ```<num_vertices>``` trata-se do número de vértices do grafo;
- - ```<edges_filename>``` trata-se do nome do arquivo que contém as arestas do grafo;

## Descrição das instâncias:
- Essas instâncias são compostas de vértices e suas arestas. O arquivo de instâncias é escrito no formato ```v``` ```w``` onde cada ```v``` representa o vértice de origem e ```w``` o vértice de destino, formando em cada linhas as arestas do grafo.

## Exemplo de uso:
- ```./main 8192 instances/rmat13.txt```
