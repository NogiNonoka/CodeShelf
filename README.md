# CodeShelf

A competitive programming (XCPC) template library.

**Author**: NogiNonoka  
**Created**: 2020-11-09  
**Last Updated**: 2026-05-31

---

## Catalogue

**Total: 70+ algorithm templates**

### ComputationalGeometry (计算几何)

| File | Algorithm | Note |
|------|-----------|------|
| `GeometryBase.cpp` | 2D Point/Vector base class | **NEW** |
| `PlaneGeometry_ConvexHull.cpp` | Andrew's monotone chain convex hull | |
| `PlaneGeometry_HalfPlaneIntersection.cpp` | Half-plane intersection | **NEW** |
| `PlaneGeometry_Point_Vector.cpp` | Point/Vector operations | |
| `PlaneGeometry_RotatingCalipers.cpp` | Rotating calipers (diameter, min dist) | **NEW** |
| `SolidGeometry_MinimumCoveringBall.cpp` | Minimum enclosing ball in 3D | |

### DataStructure (数据结构)

| File | Algorithm | Note |
|------|-----------|------|
| `BST_Splay.cpp` | Splay tree | bug fixed |
| `BST_Treap.cpp` | Treap (randomized BST) | bug fixed |
| `CartesianTree.cpp` | Cartesian tree | **NEW** |
| `DisjointUnion_PathZip.cpp` | DSU with path compression | |
| `FenwickTree.cpp` | Fenwick tree / BIT | **NEW** |
| `KD_Tree.cpp` | KD-Tree for nearest neighbor | bug fixed |
| `LiChaoSegmentTree.cpp` | Li Chao segment tree (dynamic line max) | **NEW** |
| `LinkCutTree.cpp` | Link-Cut Tree (dynamic tree) | **NEW** |
| `PersistentSegmentTree_kthQuery.cpp` | Chairman tree (range k-th) | |
| `PersistentSegmentTree_MexQuery.cpp` | Persistent seg tree for MEX | |
| `SegmentTree_Beats.cpp` | Segment Tree Beats (chmin/chmax/add) | **NEW** |
| `SegmentTree_MinMax.cpp` | Segment tree (range min/max) | refactored |
| `SegmentTree_PlusMinus.cpp` | Segment tree (range add/sum) | refactored |
| `SparseTable.cpp` | RMQ (O(1) query) | |

### GraphTheory (图论)

| File | Algorithm | Note |
|------|-----------|------|
| `BiConnectedComponents_CutVertex_Tarjan.cpp` | Tarjan articulation points | |
| `BiConnectedComponents_Edge_Tarjan.cpp` | Tarjan bridges | |
| `BipartiteGraph_HoKashyap.cpp` | Hopcroft-Karp bipartite matching | |
| `BipartiteGraph_Hungarian.cpp` | Hungarian algorithm | |
| `BipartiteGraph_KuhnMunkres.cpp` | Kuhn-Munkres (KM) weighted matching | |
| `CentroidDecomposition.cpp` | Centroid decomposition | **NEW** |
| `DifferenceConstraints.cpp` | System of difference constraints | |
| `DirectedMST_ChuLiuEdmonds.cpp` | Chu-Liu/Edmonds directed MST | **NEW** |
| `MaxClique_BronKerbosch.cpp` | Bron-Kerbosch maximum clique | |
| `MaxMatching_Blossom.cpp` | Edmonds blossom (general graph) | **NEW** |
| `MinimumSpanningTree_Kruskal.cpp` | Kruskal's MST | |
| `MinimumSpanningTree_Prim.cpp` | Prim's MST | |
| `NetworkFlow_Dicnic.cpp` | Dinic's max flow | |
| `NetworkFlow_Dicnic_zyy_nju.cpp` | Alternative Dinic | |
| `NetworkFlow_EdmondsKarp.cpp` | Edmonds-Karp max flow | |
| `NetworkFlow_ISAP.cpp` | ISAP max flow | |
| `NetworkFlow_MCMF.cpp` | Min-cost max-flow (SPFA) | **NEW** |
| `ShortestPath_BellmanFord_Queue.cpp` | SPFA | |
| `ShortestPath_Dijkstra_PriorityQueue.cpp` | Dijkstra with binary heap | |
| `StronglyConnectedComponents_Tarjan.cpp` | Tarjan SCC | |
| `TwoSAT_Tarjan.cpp` | 2-SAT (Tarjan SCC) | **NEW** |
| `VirtualTree.cpp` | Virtual tree + LCA | **NEW** |
| `WorkOnTree_BinaryIncrease_LCA.cpp` | Binary lifting LCA | |
| `WorkOnTree_HeavyLightDecomposition.cpp` | HLD | |

### MathTheory (数学)

| File | Algorithm | Note |
|------|-----------|------|
| `BerlekampMassey.cpp` | Berlekamp-Massey (linear recurrence) | **NEW** |
| `ElementaryNumberTheory_ChinaRemainderTheorem.cpp` | CRT | |
| `ElementaryNumberTheory_EulerTotientFunction.cpp` | Euler's totient | |
| `ElementaryNumberTheory_ExtendedCRT.cpp` | Extended CRT | |
| `ElementaryNumberTheory_ExtendedGCD.cpp` | Extended GCD | |
| `ElementaryNumberTheory_LinearInverseElement_ConbinatorialNumber.cpp` | Linear inverse | |
| `LinearAlgebra_GaussJordanElimination.cpp` | Gauss-Jordan elimination | fixed |
| `LinearAlgebra_LinearProgramming_Simplex.cpp` | Simplex method | |
| `LinearAlgebra_LinearProgramming_Simplex_Tilnel.cpp` | Alternative Simplex | |
| `LinearAlgebra_MatrixQuickPow.cpp` | Matrix exponentiation | fixed |
| `ModInt.cpp` | ModInt template (operator overloading) | **NEW** |
| `NumericalIntegration_Simpson.cpp` | Adaptive Simpson integration | **NEW** |
| `Polynomial_FFT.cpp` | FFT (iterative) | **optimized** |
| `Polynomial_FFT_kuangbin.cpp` | Alternative FFT | |
| `Polynomial_FWT.cpp` | Fast Walsh-Hadamard Transform | |
| `Polynomial_FWT_Subset.cpp` | Subset convolution (SOS DP) | **NEW** |
| `Polynomial_LagrangeInterpolation.cpp` | Lagrange interpolation | |
| `Polynomial_NTT.cpp` | Number Theoretic Transform | **NEW** |
| `Polynomial_Preparation.cpp` | Polynomial utilities | |
| `Preparation_QuickMul.cpp` | Fast multiplication | |
| `Preparation_QuickPow.cpp` | Binary exponentiation | |
| `Prime_EulerPrimeSieve.cpp` | Linear prime sieve | |
| `Prime_MillerRabin_PollardRho.cpp` | Miller-Rabin + Pollard Rho | **NEW** |
| `Prime_MobiusFunctionSieve.cpp` | Mobius function sieve | |

### String (字符串)

| File | Algorithm | Note |
|------|-----------|------|
| `Hash.cpp` | Rolling hash | |
| `Lydon.cpp` | Lyndon factorization | |
| `PalindromicString_Manacher.cpp` | Manacher's algorithm | |
| `PalindromicTree_Eertree.cpp` | Palindromic tree (Eertree) | **NEW** |
| `StringMatch_ACAutomaton.cpp` | Aho-Corasick automaton | |
| `StringMatch_Knuth-Morris-Pratt.cpp` | KMP | fixed |
| `SuffixArray.cpp` | Suffix array | |
| `SuffixAutomaton.cpp` | Suffix automaton | **NEW** |
| `SuffixMatch_exKMP_ZAlgorithm.cpp` | Extended KMP (Z-algorithm) | |

### Others (其他)

| File | Algorithm | Note |
|------|-----------|------|
| `FastIO.cpp` | Fast scanner (fread-based) | **NEW** |
| `MosAlgorithm.cpp` | Mo's algorithm (sqrt decomposition) | **NEW** |

### AlgorithmIntroduction (算法导论文档)

Markdown documentation with embedded code templates:

- `DataStructure/SegmentTree.md`
- `GraphTheory/BipartiteGraph.md`
- `GraphTheory/MinimumSpanningTree.md`
- `GraphTheory/NetworkFlow.md`
- `MathTheory/Combinatorics.md`
- `MathTheory/ElementaryNumberTheory.md`
- `MathTheory/Polynomial.md`
- `String/PalindromicString.md`
- `String/StringMatch.md`
- `String/SuffixArray.md`

---

## Changelog

### 2026-05-31
- **NEW**: Add 25 algorithm templates (P0/P1/P2)
- **NEW**: Add ModInt base class and 2D geometry base class
- **FIX**: KD-Tree division by zero, Splay remove() missing return, Treap rand() seeding
- **FIX**: Matrix quickpow overflow (add modular arithmetic)
- **FIX**: KMP missing function implementations
- **FIX**: Convex Hull epsilon comparison, Gauss-Jordan complexity annotation
- **REFACTOR**: SegmentTree dynamic allocation → static memory pool
- **PERF**: FFT recursive → iterative Cooley-Tukey

---

## C++ CodeStyleGuide

### Files
- Name as `$AlgorithmName.cpp`

### Headers
- Permit but Not Recommend using `bits/stdc++.h`
- Do **Not** Use `#define` for Constants, using `const` instead

### Comments
- Analyze **Time** and Space Complexity

### Algorithm
- Recommend using **Struct / Template** for Data Structure and Algorithm
- Add a **DEBUG** part / function
- (Optional) Add a **Problem ID** with a **Link**

### Constants Template
```cpp
// Optional
// #define int long long
// #define double long double
// #define endl "\n"
// const int MAXN = ;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};
```
