# TD2 de programmation C++

Les deux exercices suivent le style du TD1 : classes simples, noms explicites,
gardes d'inclusion, `std::`, exceptions et tests avec une fonction `verifier`.
Aucune bibliotheque externe n'est necessaire. Le code est compile en C++11.

## Organisation

```text
TD2_CPP/
├── .gitignore
├── README.md
├── exercice1/
│   ├── SearchingAlgorithm.h / SearchingAlgorithm.cpp
│   ├── LinearSearch.h / LinearSearch.cpp
│   ├── JumpSearch.h / JumpSearch.cpp
│   ├── BinarySearch.h / BinarySearch.cpp
│   └── main.cpp
└── exercice2/
    ├── MatrixBase.h
    ├── MatrixNumerical.h
    └── main.cpp
```

Les classes ordinaires ont une interface `.h` et une implementation `.cpp`.
Les definitions des templates sont dans les `.h`, apres les declarations,
car le compilateur doit les voir pour chaque type utilise. Le cours procede
ainsi avec `Array<T>` (page 59). La copie et l'affectation des matrices sont
celles generees par le compilateur : les vecteurs sont copies independamment.

## Compilation et execution sous WSL Ubuntu

Depuis le dossier du depot :

```bash
cd /mnt/c/Users/bouch/Documents/TD_CPP
mkdir -p TD2_CPP/build
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror TD2_CPP/exercice1/*.cpp -o TD2_CPP/build/exercice1
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror TD2_CPP/exercice2/main.cpp -o TD2_CPP/build/exercice2
./TD2_CPP/build/exercice1
./TD2_CPP/build/exercice2
```

Chaque programme affiche ses verifications et renvoie 0 en cas de succes,
1 en cas d'echec. Le dossier `build/` est ignore par Git : executables et
journaux de test ne sont pas versionnes.

## Exercice I : questions 1 a 5

| Question | Realisation |
| --- | --- |
| 1 | `SearchingAlgorithm` : `numberComparisons`, `totalComparisons`, `totalSearch`, `averageComparisons` et accesseurs. |
| 2 | Constructeur par defaut : compteur individuel initialise a zero ; les statiques sont initialisees une seule fois dans le `.cpp`. |
| 3 | `search(const std::vector<int>&, int)` virtuelle pure, indice a partir de 0 ou `-1`. |
| 4 | `displaySearchResults(std::ostream&, int results, int target)` : resultat, comparaisons, total, nombre de recherches et moyenne. |
| 5 | `LinearSearch`, `JumpSearch`, `BinarySearch`, derivees de la classe abstraite. |

La photo semble ecrire `BiarySearch` ; le nom `BinarySearch` de tes consignes
est retenu pour la recherche dichotomique.

### Principe des recherches

- `LinearSearch` parcourt les elements du debut a la fin. Le vecteur peut etre non trie.
- `JumpSearch` avance par blocs de taille entiere `sqrt(n)`, puis parcourt le bloc candidat.
- `BinarySearch` compare l'element central, puis conserve la moitie pertinente.

`JumpSearch` et `BinarySearch` exigent un vecteur trie en ordre croissant
(doublons autorises). Elles ne le trient pas et ne verifient pas son tri :
cela ajouterait un parcours complet. Avec des doublons, un indice valide suffit ;
la dichotomie ne garantit pas la premiere occurrence.

### Convention de comptage

Une comparaison est une evaluation de `==` ou `<` entre une valeur du vecteur
et la cible. Les comparaisons d'indices et les conditions de boucle ne sont
pas comptees. En dichotomie, une egalite ratee suivie de `<` compte donc deux
comparaisons. Un vecteur vide en demande zero, mais compte comme une recherche.

`beginSearch` remet le compteur individuel a zero. `endSearch` compte chaque
recherche terminee et conserve ses comparaisons dans une somme statique en
attente. `displaySearchResults` actualise le total et la moyenne a partir de
cette somme, puis la remet a zero. Les accesseurs du total et de la moyenne
font la meme actualisation. Ce petit mecanisme evite a la fois les doubles
comptages lors d'un reaffichage et la perte des recherches non affichees.
Les statistiques sont partagees par toutes les instances et les trois classes.
Le constructeur d'une nouvelle instance ne les reinitialise pas.

Pour afficher un resultat individuel, appeler `displaySearchResults` apres
le `search` correspondant, avant une nouvelle recherche sur le meme objet.
Le compteur individuel correspond toujours a sa derniere recherche.

Exemple sur `{1, 3, 5, 7, 9, 11, 13, 15, 17}` :

| Cible | Indice | LinearSearch | JumpSearch | BinarySearch |
| --- | --- | --- | --- | --- |
| 9 | 4 | 5 | 4 | 1 |
| 1 | 0 | 1 | 2 | 5 |
| 17 | 8 | 9 | 6 | 7 |
| 8 | -1 | 9 | 5 | 8 |
| 0 | -1 | 9 | 4 | 6 |
| 20 | -1 | 9 | 3 | 8 |

Les tests couvrent ces nombres exacts, le vecteur vide, un element unique,
les flux d'affichage, les statiques, les recherches repetees et le polymorphisme.
Un parcours supplementaire effectue 2706 recherches sur des tailles de 0 a 40,
avec doublons et derniers blocs incomplets.

## Exercice II : questions 1 a 12

| Question | Realisation |
| --- | --- |
| 1 | `MatrixBase<T>` : `data` en `std::vector<std::vector<T> >`, `rows` et `cols` en `std::size_t`. |
| 2 | Constructeurs par defaut (0 x 0), par dimensions, depuis un vecteur 2D ; copie automatique. |
| 3 | `addElement(ligne, colonne, valeur)` et `getElement(ligne, colonne)` avec controle des indices. |
| 4 | `getRows()` et `getCols()`. |
| 5 | `Display(std::ostream& = std::cout)`. |
| 6 | `MatrixNumerical<T>` herite publiquement de `MatrixBase<T>` ; utilisation avec `int`, `float`, `double`. |
| 7 | `getDeterminant()` par developpement selon la premiere ligne. |
| 8 | Constructeurs correspondants dans `MatrixNumerical<T>`. |
| 9 | Operateurs `+`, `-`, `*` avec verification des dimensions. |
| 10 | `getInverse()` par cofacteurs ; fonction template libre `getCoFactor`. |
| 11 | Operateur `/` defini par `A / B = A * inverse(B)`. |
| 12 | Fonction statique `getIdentity(int taille)`. |

### Conventions et calculs

Les indices commencent a zero. `addElement` place ou remplace la valeur d'une
case existante ; il ne change pas la taille de la matrice. Un vecteur 2D doit
etre rectangulaire. `MatrixBase` accepte aussi des types non numeriques,
comme `std::string`. Le parametre de `MatrixNumerical` doit supporter
l'arithmetique numerique ; aucune metaprogrammation de restriction n'est ajoutee.

Le cofacteur `C(i,j)` est `(-1)^(i+j)` multiplie par le determinant de la
matrice obtenue en supprimant la ligne `i` et la colonne `j`.
La fonction libre `getCoFactor` retourne ce nombre signe.
Le determinant se calcule par `somme(A(0,j) * C(0,j))`.
L'inverse se calcule par `inverse(A)(j,i) = C(i,j) / det(A)` : l'echange
des indices transpose la matrice des cofacteurs.

- `+` et `-` exigent les memes dimensions ; `*` exige `A.cols == B.rows`.
- `/` exige un diviseur carre, non vide et inversible, et `A.cols == B.rows`.
- `+`, `-`, `*` et le determinant conservent le type `T`.
- L'inverse et la division renvoient `MatrixNumerical<double>`, y compris
  pour une matrice entiere, afin de conserver les fractions.
- Le determinant d'une matrice 0 x 0 vaut 1 par convention. Cela donne le
  bon cofacteur pour une matrice 1 x 1. L'inverse vide est refuse.
- `getIdentity` exige une taille strictement positive.
- Les dimensions incompatibles levent `std::invalid_argument`, les indices
  invalides `std::out_of_range`, et un determinant nul `std::domain_error`
  lors d'une inversion.

Exemple : pour `A = {{4,7},{2,6}}`, le determinant vaut 10 et l'inverse vaut
`{{0.6,-0.7},{-0.2,0.4}}`.

Cette methode pedagogique convient aux petites matrices : le developpement
recursif est couteux pour les grandes tailles. Les calculs flottants restent
approximatifs, notamment pres d'une matrice singuliere ; le test du determinant
nul ne constitue pas une analyse de stabilite numerique. Les calculs de type
`int` supposent que les resultats intermediaires restent representables.

Les tests comparent les valeurs a des resultats connus, puis verifient notamment
`A * inverse(A) = I`, les deux sens du produit, les tailles 1 a 4, les matrices
rectangulaires, les types numeriques et les exceptions. Les comparaisons de
resultats flottants utilisent une tolerance de `1e-9`.

## Validation et correspondance avec le cours

Compilation avec g++ 13.3.0 : aucun avertissement avec les options ci-dessus.
Execution : **200 verifications pour l'exercice I, 45 pour l'exercice II,
zero erreur**, avec les 2706 recherches supplementaires incluses dans la
derniere verification de l'exercice I.

References au cours fourni de J. M. Perronne : organisation en modules p. 2,
classes et constructeurs p. 32-39, statiques p. 41-42, copie et affectation
p. 43-44, classes abstraites et heritage p. 47-53, exceptions p. 54-57 et 61,
templates p. 58-60, vecteurs et flux p. 63-69. Les algorithmes de recherche
et les formules matricielles sont ceux demandes par le sujet du TD2.
