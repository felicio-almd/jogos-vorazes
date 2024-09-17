<div align="center" id="top"> 
  <img src="./.github/app.gif" alt="Jogos Vorazes" />

  &#xa0;
</div>

<h1 align="center">Jogos Vorazes</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/felicio-almd/jogos-vorazes?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/felicio-almd/jogos-vorazes?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/felicio-almd/jogos-vorazes?color=56BEB8">

  <img alt="Github forks" src="https://img.shields.io/github/forks/felicio-almd/jogos-vorazes?color=56BEB8" />

</p>

<p align="center">
  <a href="#dart-Sobre-o-projeto">Sobre</a> &#xa0; | &#xa0; 
  <a href="#sparkles-funcionalidades">Funcionalidades</a> &#xa0; | &#xa0;
  <a href="#rocket-tecnologias">Tecnologias</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requisitos">Requisitos</a> &#xa0; | &#xa0;

</p>

<br>

## :dart: Sobre o projeto ##

Projeto para disciplina de Estrutura de Dados 1


:memo: Resumo do Funcionamento do Código
O programa simula um labirinto dos Jogos Vorazes, onde um tributo deve encontrar a saída enquanto evita os "bestantes" (monstros). O código funciona da seguinte maneira:

Lê as dimensões e o layout do labirinto da entrada padrão.
Converte o labirinto em uma matriz de inteiros para processamento.
Localiza a posição inicial do tributo e dos bestantes.
Utiliza um algoritmo de busca em profundidade (DFS) modificado para encontrar um caminho até a saída.
Durante a busca, os bestantes se movem pelo labirinto.
Se um caminho for encontrado, imprime "YES" seguido pelo número de movimentos e a sequência de direções.
Se não for possível encontrar um caminho, imprime "NO".

O código utiliza estruturas de dados como pilhas (para armazenar o caminho) e filas (para gerenciar as posições dos bestantes), implementando funções para manipular essas estruturas e realizar a busca no labirinto.

## :sparkles: Funcionalidades ##
:heavy_check_mark: Leitura e processamento de labirintos;
:heavy_check_mark: Busca de caminho para a saída do labirinto;
:heavy_check_mark: Movimentação de bestantes no labirinto;
:heavy_check_mark: Impressão do caminho encontrado.

## :rocket: Tecnologias ##

As seguintes ferramentas foram usadas neste projeto:

 - [C]

## :white_check_mark: Requisitos ##
Antes de começar :checkered_flag:, você precisa ter o Git e o compilador C (com mingw, se necessário) instalados.

## :checkered_flag: Começando ##

```bash
# Clone o projeto
$ git clone https://github.com/felicio-almd/jogos-vorazes

# Acessar
$ cd jogos-vorazes

$ make all 
# se estiver no CMD mingw32-make

$./maze # linux
$.\maze # windows(cmd)
```


Made by </br> <a href="https://github.com/felicio-almd" target="_blank">Felicio</a>
</br>
  <a href="https://github.com/Hizzo0" target="_blank">Italo</a>
</br>
  <a href="https://github.com/Allyson777" target="_blank">Allyson</a>

&#xa0;

<a href="#top">Back to top</a>
