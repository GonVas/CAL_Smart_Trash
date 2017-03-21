# CAL_Smart_Trash
CAL Smart Trash 2016, by Diogo Pereira, Eduarda Cunha, Gonçalo Moreno

Project specification by prof. Rosaldo Rossetti (rossetti@fe.up.pt):

" Tema 4: Recolha de Lixo Inteligente
Num sistema tradicional de recolha de lixo, um camião de resíduos passa por todos os pontos de recolha espalhados na cidade, recolhendo o conteúdo dos contentores e transportando-o para um aterro sanitário. Sistemas contemporâneos, entretanto, estimulam a reciclagem, espalhando na cidade contentores específicos para o efeito; o conteúdo, neste caso, é levado para uma estação de tratamento de resíduos onde é tratado adequadamente. 
Considere um sistema de coleta inteligente, onde os contentores estão equipados com sensores de volume, que indicam o momento em que o seu conteúdo precisa ser coletado. Desta forma, os camiões não precisam realizar viagens periódicas, mas apenas realizam o itinerário que inclui contentores cheios.
O sistema a ser desenvolvido deverá considerar a monitorização dos contentores, a partir de sensores de volume, e a capacidade dos veículos de recolha, em função do tipo de resíduo (considere recolha seletiva), a fim de determinar o melhor itinerário a executar, desde a garagem dos veículos, passando pelo maior número de pontos de recolha, até à estação de tratamento de resíduos.
Considere o efeito de frotas homogêneas (com um só tipo de veículo de recolha), assim como frotas heterogêneas (com veículos para cada tipo de resíduo). Considere também a possibilidade de haver mais do que uma garagem, e estações de tratamento, espalhadas na rede, e o seu efeito na eficiência dos algoritmos que implementar.

Avalie a conectividade do grafo, a fim de evitar que locais de pontos de recolha se encontrem em zonas inacessíveis a partir do ponto onde se encontra as garagens e as estações de tratamento.

Considere a possibilidade de utilizar mapas reais, extraídos do OpenStreetMaps (www.openstreetmap.org), localizando, no mapa, os respectivos locais de recolha, das garagens, e das estações de tratamento. "

This problem is a subset of the TSP (Travelling Salesman Problem) , the asymetric TSP problem. 
Links and resources for this problem:
https://en.wikipedia.org/wiki/Travelling_salesman_problem
https://en.wikipedia.org/wiki/Concorde_TSP_Solver
http://nbviewer.jupyter.org/url/norvig.com/ipython/TSP.ipynb ##Very good resource##

Technical specifications:
	Main algorithm is going to be written in C++.
	Parser of openstreetmaps is going to be in python ( with lxml library). 
	Interface can be in pyhton with pyQt.
	Test driven Development (TDB) with CUTE for C++.
