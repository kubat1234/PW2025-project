# Przyspieszenie zadania *Taksówki*

## Tresć Zadania

### [statement.pdf](statement.pdf)

W skrócie dany jest graf oraz zapytania czy pomiędzy dwoma wierzchołkami da się przejść dokładnie w *d* krokach.

## Rozwiązanie bez optymalizacji

### [slow.cpp](slow.cpp)

Pytanie czy pomiędzy dwoma wierzchołkami da się przejść dokładnie w *d* krokach jest równoważne pytaniu czy istnieje pomiędzy a i b ścieżka <= d o takiej samej parzystości (gdy dojdziemy z a do b to możemy się cofac o jedną krawędź, i przejść nią znowu to b dopóki nie otrzymamy ścieżki dlugości d)

Rozwiązanie z każdego wierzchołka puszcza zmodyfikowany algorytm bfs, trzymający jako stan aktualny wierzchołek oraz odległość od startu oraz uzywa tablicy `int dist[n][2]`, która dla każdego wierzchołka trzyma odległość od startu dla danej parzystości.

## Optymalizacje na jednym wątku

### [optimized.cpp](optimized.cpp)
- tablica `int dist[n][2];` w funkcji `main` zamiast tworzenia vectora w kazdej iteracji pętli
- Używanie int zamiast short int i bool
- zmienna p zamiast d%2 i np zamiast (d+1)%2

### [optimized2.cpp](optimized2.cp)
- kolejka `queue<int> q;` alokowana przed pętlą, pętla `while(!q.empty())` zapewnia że kolejka będzie pusta dla każdej iteracji pętli

## Optymalizacje wielowątkowe
- każde wywołanie głównej pętli to wykonanie algorytmu bsf zaczynając w wierzchołku *i* i jest niezależne iteracji pętli dla innych wierzchołków, więc można wykonywać tą pętlę na wielu wątkach jednocześnie
- Należeło zmienić `vector<bool> ans(k);` na `vector<int> ans(k);`, ponieważ vector booli trzyma kolejne 32 bity jako jeden int, więc operacje nie są thread safe

## Optymalizacje z uzuciem **std::thread**

### [thread.cpp](thread.cpp)
- Wykonywanie głównej pętli współbieżnie przez wątki
```cpp
vector<thread> threads;
for(int t_id = 0; t_id < num_threads; t_id++){
    threads.emplace_back([&, t_id](){
        for(int i = t_id; i < n; i += num_threads){
```

### [thread2.cpp](thread2.cpp)
- Użycie optymalnej liczby wątków `const int num_threads = std::thread::hardware_concurrency();`
- alokowanie tablicy dist i kolejki jeden raz dla wątku
```cpp
threads.emplace_back([&, t_id](){
    int dist[n][2];
    queue<pair<int,int>> q;
    for(int i = t_id; i < n; i += num_threads){
```

## Optymalizacje z uzyciem biblioteki **OpenMP**

### [omp.cpp](omp.cpp)
- dodanie `#pragma omp parallel for` przed główną pętlą

### [omp2.cpp](omp2.cpp)
- tablica dist i kolejka alokują sie raz dla każdego wątku
- uzycie dynamicznego przydzielania wątków
``` cpp
#pragma omp parallel
{
    int dist[n][2];
    queue<pair<int,int>> q;
    #pragma omp for schedule(dynamic)
    for(int i = 0; i < n; i++){
```

## Czasy wykonania
| | Mój Laptop | Serwer Student |
| --- | --- | --- |
| slow.cpp | 10.16s | |
| optimized.cpp | 5.15s | |
| optimized2.cpp | 2.45s | |
| thread.cpp | 1.39s | |
| thread2.cpp | 1.37s | |
| omp.cpp | 1.42s | |
| omp2.cpp | 1.36s | |


