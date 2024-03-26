#include <random>
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

using namespace lasd;

std::string randomString(){
  char alfa[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  std::default_random_engine gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(0,25);

  std::string rnd = "";

  for(uint i=0;i<dist(gen);i++){
    rnd = rnd + alfa[dist(gen)];
  }

  return rnd;
}

int randomInt(){
  std::default_random_engine gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(0,100);

  return dist(gen);
}

float randomFloat(){
  std::default_random_engine gen(std::random_device{}());
  std::uniform_real_distribution<float> dist(0.0,100.0);

  return roundf(dist(gen) * 100)/100.0;
}

double randomDouble(){
  std::default_random_engine gen(std::random_device{}());
  std::uniform_real_distribution<double> dist(0.0,100.0);

  return roundf(dist(gen) * 100)/100.0;
}

template <typename Data>
void MapPrint(const Data& dato, void* _){
  std::cout<<dato<<std::endl;
}

void MapDouble(int& dato, void* _) {
  dato *= 2;
}

void MapTriple(int& dato, void* _) {
  dato *= 3;
}

void MapSquare(float& dato, void* _) {
  dato = roundf(std::pow(dato,2) * 100)/100.0;
}

void MapCube(float& dato, void* _) {
  dato = roundf(std::pow(dato,3) * 100)/100.0;
}

void MapUpper(std::string& dato, void* _) {
  std::transform(dato.begin(),dato.end(),dato.begin(), ::toupper);
}

void MapConcat(std::string& dato, void* str){
  dato = *((std::string*) str) + dato;
}

void AuxFoldSum(const int& dato, const void* lim, void* sum)noexcept{
  if(dato < *((int*) lim)){
    *((int*) sum) = *((int*) sum) + dato;
  }
}

void AuxFoldProdInt(const float& dato, const void* lim, void* prod)noexcept{
  if(dato < *((int*) lim)){
    *((int*) prod) = *((int*) prod) * dato;
  }
}

void AuxFoldProd(const float& dato, const void* lim, void* prod)noexcept{
  if(dato > *((float*) lim)){
    *((float*) prod) = *((float*) prod) * dato;
  }
}

void AuxFoldSumFloat(const int& dato, const void* lim, void* sum)noexcept{
  if(dato > *((float*) lim)){
    *((float*) sum) = *((float*) sum) + dato;
  }
}

void AuxFoldSumDouble(const int& dato, const void* lim, void* sum)noexcept{
  if(dato > *((double*) lim)){
    *((double*) sum) = *((double*) sum) + dato;
  }
}

void AuxFoldConcat(const std::string& dato, const void* lim, void* str)noexcept{
  if(dato.size() <= *((int*) lim)){
    *((std::string*) str) = *((std::string*) str) + dato;
  }
}

template <typename Data>
void Visual(LinearContainer<Data>& cont){
  std::cout<<"Visualizza elementi\n1:Front\n2:Back\n3:Index\n0:Exit"<<std::endl;
  uint visual;
  std::cin>>visual;

  switch(visual){
    case 1:
    {
      std::cout<<cont.Front()<<std::endl;
      break;
    }
    case 2:
    {
      std::cout<<cont.Back()<<std::endl;
      break;
    }
    case 3:
    {
      uint i;

      std::cout<<"Inserisci un indice:"<<std::endl;
      std::cin>>i;

      std::cout<<cont[i]<<std::endl;
      break;
    }
  }
}

template <typename Data>
void Mod(List<Data>& list){
  std::cout<<"Modifica lista\n1:Inserimento in testa\n2:Inserimento in coda\n3:Remove\n4:Front&Remove\n0:Exit"<<std::endl;
  uint mod;
  std::cin>>mod;

  switch(mod){
    case 1:
    {
      Data dato;
      std::cout<<"Inserisci un elemento in testa:"<<std::endl;
      std::cin>>dato;

      list.InsertAtFront(dato);
      break;
    }
    case 2:
    {
      Data dato;
      std::cout<<"Inserisci un elemento in coda:"<<std::endl;
      std::cin>>dato;

      list.InsertAtBack(dato);
      break;
    }
    case 3:
    {
      list.RemoveFromFront();
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    }
    case 4:
    {
      std::cout<<list.FrontNRemove()<<std::endl;
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    }
  }
}

template <typename Data>
void Print(BinaryTree<Data>& tree){
  std::cout<<"Visualizza elementi\n1:Breadth\n2:PreOrder\n3:PostOrder\n4:InOrder\n0:Exit"<<std::endl;
  uint visual;
  std::cin>>visual;

  switch(visual){
    case 1:
      tree.MapBreadth(&MapPrint<Data>,nullptr);
      break;
    case 2:
      tree.MapPreOrder(&MapPrint<Data>,nullptr);
      break;
    case 3:
      tree.MapPostOrder(&MapPrint<Data>,nullptr);
      break;
    case 4:
      tree.MapInOrder(&MapPrint<Data>,nullptr);
      break;
  }
}

template <typename Data>
void Esiste(FoldableContainer<Data>& container){
  std::cout<<"Esistenza valore\nInserisci il valore:"<<std::endl;
  Data val;
  std::cin>>val;

  std::cout<<((container.Exists(val)) ? "PRESENTE" : "NON PRESENTE")<<std::endl;
}

void Sum(FoldableContainer<int>& container){
  std::cout<<"Somma interi minori di n"<<std::endl;
  int acc = 0;
  std::cout<<"Inserisci n:"<<std::endl;
  int n;
  std::cin>>n;
  
  container.Fold(&AuxFoldSum,&n,&acc);

  std::cout<<acc<<std::endl;
}

void ProdInt(FoldableContainer<int>& container){
  std::cout<<"Prodotto interi minori di n"<<std::endl;
  int acc = 1;
  std::cout<<"Inserisci n:"<<std::endl;
  int n;
  std::cin>>n;
  
  container.Fold(&AuxFoldProdInt,&n,&acc);

  std::cout<<acc<<std::endl;
}

void Prod(FoldableContainer<float>& container){
  std::cout<<"Prodotto float maggiori di n"<<std::endl;
  float acc = 1;
  std::cout<<"Inserisci n:"<<std::endl;
  float n;
  std::cin>>n;
  
  container.Fold(&AuxFoldProd,&n,&acc);

  std::cout<<acc<<std::endl;
}

void SumFloat(FoldableContainer<float>& container){
  std::cout<<"Somma float maggiori di n"<<std::endl;
  float acc = 0;
  std::cout<<"Inserisci n:"<<std::endl;
  float n;
  std::cin>>n;
  
  container.Fold(&AuxFoldSumFloat,&n,&acc);

  std::cout<<acc<<std::endl;
}

void SumDouble(FoldableContainer<double>& container){
  std::cout<<"Somma double maggiori di n"<<std::endl;
  double acc = 0;
  std::cout<<"Inserisci n:"<<std::endl;
  double n;
  std::cin>>n;
  
  container.Fold(&AuxFoldSumDouble,&n,&acc);

  std::cout<<acc<<std::endl;
}

void Concat(FoldableContainer<std::string>& container){
  std::cout<<"Concatenazione stringhe con lunghezza minore o uguale ad n"<<std::endl;
  std::string acc = "";
  std::cout<<"Inserisci n:"<<std::endl;
  int n;
  std::cin>>n;

  container.Fold(&AuxFoldConcat,&n,&acc);

  std::cout<<acc<<std::endl;
}

template <typename Data>
void menuStack(Stack<Data>& stack){
  std::cout<<"Operazioni\n1:Push\n2:Pop\n3:TopNPop\n4:Top\n5:Empty\n6:Size\n7:Clear\n0:Exit"<<std::endl;
  uint op;
  std::cin>>op;

  while(op != 0){
    switch(op){
    case 1:
    {
      std::cout<<"Inserisci elemento:"<<std::endl;
      Data ele;
      std::cin>>ele;

      stack.Push(ele);
      break;
    }
    case 2:
      stack.Pop();
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    case 3:
      std::cout<<stack.TopNPop()<<std::endl;
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    case 4:
      std::cout<<stack.Top()<<std::endl;
      break;
    case 5:
      std::cout<<((stack.Empty()) ? "VUOTO" : "NON VUOTO")<<std::endl;
      break;
    case 6:
      std::cout<<"Dim effettiva:"<<stack.Size()<<std::endl;
      break;
    case 7:
      stack.Clear();
      std::cout<<"Stack svuotato"<<std::endl;
      break;
    }

    std::cout<<"Operazioni\n1:Push\n2:Pop\n3:TopNPop\n4:Top\n5:Empty\n6:Size\n7:Clear\n0:Exit"<<std::endl;
    std::cin>>op;
  }
}

template <typename Data>
void menuQueue(Queue<Data>& queue){
  std::cout<<"Operazioni\n1:Enqueue\n2:Dequeue\n3:HeadNDequeue\n4:Head\n5:Empty\n6:Size\n7:Clear\n0:Exit"<<std::endl;
  uint op;
  std::cin>>op;

  while(op != 0){
    switch(op){
    case 1:
    {
      std::cout<<"Inserisci elemento:"<<std::endl;
      Data ele;
      std::cin>>ele;

      queue.Enqueue(ele);
      break;
    }
    case 2:
      queue.Dequeue();
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    case 3:
      std::cout<<queue.HeadNDequeue()<<std::endl;
      std::cout<<"Elemento rimosso"<<std::endl;
      break;
    case 4:
      std::cout<<queue.Head()<<std::endl;
      break;
    case 5:
      std::cout<<((queue.Empty()) ? "VUOTO" : "NON VUOTO")<<std::endl;
      break;
    case 6:
      std::cout<<"Dim effettiva:"<<queue.Size()<<std::endl;
      break;
    case 7:
      queue.Clear();
      std::cout<<"Queue svuotata"<<std::endl;
      break;
    }

    std::cout<<"Operazioni\n1:Enqueue\n2:Dequeue\n3:HeadNDequeue\n4:Head\n5:Empty\n6:Size\n7:Clear\n0:Exit"<<std::endl;
    std::cin>>op;
  }
}

template <typename Data>
void menuNodo(BinaryTree<Data>& tree){
  std::cout<<"Operazioni\n1:Accesso nodo\n2:Esistenza\n3:Accesso figli\n4:Iteratori\n0:Exit"<<std::endl;
  uint op;
  std::cin>>op;

  while(op != 0){
    switch(op){
    case 1:
      std::cout<<"Accesso lettura: " <<tree.Root().Element()<<std::endl;

      std::cout<<"Accesso scrittura: " <<tree.Root().Element()<<std::endl;
      break;
    case 2:
      std::cout<<"Figlio sinistro: " <<(tree.Root().HasLeftChild() ? "PRESENTE" : "NON PRESENTE")<<std::endl;

      std::cout<<"Figlio destro: " <<(tree.Root().HasRightChild() ? "PRESENTE" : "NON PRESENTE")<<std::endl;
      break;
    case 3:
      std::cout<<"Figlio sinistro: " <<tree.Root().LeftChild().Element()<<std::endl;

      std::cout<<"Figlio destro: " <<tree.Root().RightChild().Element()<<std::endl;
      break;
    case 4:
      {
        BTPostOrderIterator<Data> iterator(tree);

        std::cout<<"Nodo puntato: "<<*iterator<<std::endl;

        std::cout<<"Iteratore\n1:next\n0:Exit"<<std::endl;
        uint itr;
        std::cin>>itr;

        while(*iterator!=tree.Root().Element() && itr!=0){
          ++iterator;
          std::cout<<"Nodo puntato: "<<*iterator<<std::endl;

          if(*iterator!=tree.Root().Element()){
            std::cout<<"Iteratore\n1:next\n0:Exit"<<std::endl;
            std::cin>>itr;
          }
          else{
            std::cout<<"TERMINATO"<<std::endl;
          }
        }
      
      break;
      }
    }

    std::cout<<"Operazioni\n1:Accesso nodo\n2:Esistenza\n3:Accesso figli\n4:Iteratori\n0:Exit"<<std::endl;
    std::cin>>op;
  }
}

template <typename Data>
void menuBST(BST<Data>& tree){
  std::cout<<"Operazioni\n1:Insert\n2:Mod\n0:Exit"<<std::endl;
  uint op;
  Data ele;
  std::cin>>op;

  while(op != 0){
    switch(op){
      case 1:{
        std::cout<<"Inserisci elemento:"<<std::endl;
        std::cin>>ele;

        std::cout<<"Elemento "<<(tree.Insert(ele) ? "inserito" : "non inserito")<<std::endl;
      }
        break;
      case 2:{
        std::cout<<"Operazioni\n1:RemoveMin\n2:RemoveMax\n3:MinNRemove\n4:MaxNRemove\n5:Min\n6:Max\n7:RemoveSucc\n8:RemovePred\n9:SuccNRemove\n10:PredNRemove\n11:Succ\n12:Pred"<<std::endl;
        uint mod;
        std::cin>>mod;

        switch(mod){
          case 1:
            tree.RemoveMin();
            break;
          case 2:
            tree.RemoveMax();
            break;
          case 3:
            std::cout<<"Min: "<<tree.MinNRemove()<<std::endl;
            break;
          case 4:
            std::cout<<"Max: "<<tree.MaxNRemove()<<std::endl;
            break;
          case 5:
            std::cout<<"Min: "<<tree.Min()<<std::endl;
            break;
          case 6:
            std::cout<<"Max: "<<tree.Max()<<std::endl;
            break;
          case 7:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;

            tree.RemoveSuccessor(ele);
            break;
          case 8:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;
            
            tree.RemovePredecessor(ele);
            break;
          case 9:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;
            
            std::cout<<"Succ: "<<tree.SuccessorNRemove(ele)<<std::endl;
            break;
          case 10:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;
            
            std::cout<<"Pred: "<<tree.PredecessorNRemove(ele)<<std::endl;
            break;
          case 11:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;
            
            std::cout<<"Succ: "<<tree.Successor(ele)<<std::endl;
            break;
          case 12:
            std::cout<<"Inserisci elemento:"<<std::endl;
            std::cin>>ele;
            
            std::cout<<"Pred: "<<tree.Predecessor(ele)<<std::endl;
            break;
        }
      }
        break;
    }

    std::cout<<"Operazioni\n1:Insert\n2:Mod\n0:Exit"<<std::endl;
    std::cin>>op;
  }
}

template <typename Data>
void ModHash(HashTable<Data>& table){
  std::cout<<"Operazioni\n1:Insert\n2:Remove\n0:Exit"<<std::endl;
  uint op;
  Data ele;
  std::cin>>op;

  switch(op){
    case 1:
      std::cout<<"Inserisci elemento:"<<std::endl;
      std::cin>>ele;

      std::cout<<"Elemento "<<(table.Insert(ele) ? "inserito" : "non inserito")<<std::endl;
      break;
    case 2:
      std::cout<<"Inserisci elemento:"<<std::endl;
      std::cin>>ele;

      std::cout<<"Elemento "<<(table.Remove(ele) ? "rimosso" : "non rimosso")<<std::endl;  
      break;
  }

}

void menu(){
  uint strutt,tipo,dim,newdim,op,imp;

  std::cout<<"Menu\nScelta struttura:\n1:Vector\n2:List\n3:Stack\n4:Queue\n5:BinaryTree\n6:BST\n7:HashTable\n0:Exit"<<std::endl;
  std::cin>>strutt;
  switch(strutt){
    case 1:
      std::cout<<"Inserisci la dimensione:"<<std::endl;
      std::cin>>dim;
      std::cout<<"Vector"<<std::endl;
      std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
      std::cin>>tipo;
      switch(tipo){
        case 1:
        {
          std::cout<<"Intero"<<std::endl;
          
          Vector<int> vector(dim);

          for(uint i=0;i<vector.Size();i++){
            vector[i] = randomInt();
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(vector);
              break;
            case 2:
              vector.Map(&MapPrint<int>,nullptr);
              break;
            case 3:
              Esiste(vector);
              break;
            case 4:
              Sum(vector);
              break;
            case 5:
              std::cout<<"2n per gli interi"<<std::endl;
              vector.Map(&MapDouble, nullptr);
              break;
            case 6:
              std::cout<<"Inserisci la nuova dim:"<<std::endl;
              std::cin>>newdim;

              if(newdim > vector.Size()){
                uint oldsize = vector.Size();
                vector.Resize(newdim);

                for(uint i=oldsize;i<vector.Size();i++){
                  vector[i] = randomInt();
                }
              }
              else{
                vector.Resize(newdim);
              }
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 2:
        {
          std::cout<<"Float"<<std::endl;
          
          Vector<float> vector(dim);

          for(uint i=0;i<vector.Size();i++){
            vector[i] = randomFloat();
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(vector);
              break;
            case 2:
              vector.Map(&MapPrint<float>,nullptr);
              break;
            case 3:
              Esiste(vector);
              break;
            case 4:
              Prod(vector);
              break;
            case 5:
              std::cout<<"n^2 per i float"<<std::endl;
              vector.Map(&MapSquare, nullptr);
              break;
            case 6:
              std::cout<<"Inserisci la nuova dim:"<<std::endl;
              std::cin>>newdim;

              if(newdim > vector.Size()){
                uint oldsize = vector.Size();
                vector.Resize(newdim);

                for(uint i=oldsize;i<vector.Size();i++){
                  vector[i] = randomFloat();
                }
              }
              else{
                vector.Resize(newdim);
              }
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 3:
        {
          std::cout<<"String"<<std::endl;
          
          Vector<std::string> vector(dim);

          for(uint i=0;i<vector.Size();i++){
            vector[i] = randomString();
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(vector);
              break;
            case 2:
              vector.Map(&MapPrint<std::string>,nullptr);
              break;
            case 3:
              Esiste(vector);
              break;
            case 4:
              Concat(vector);
              break;
            case 5:
              std::cout<<"Uppercase per le stringhe"<<std::endl;
              vector.Map(&MapUpper, nullptr);
              break;
            case 6:
              std::cout<<"Inserisci la nuova dim:"<<std::endl;
              std::cin>>newdim;

              if(newdim > vector.Size()){
                uint oldsize = vector.Size();
                vector.Resize(newdim);

                for(uint i=oldsize;i<vector.Size();i++){
                  vector[i] = randomString();
                }
              }
              else{
                vector.Resize(newdim);
              }
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Resize\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
      }
      break;
    case 2:
      std::cout<<"Inserisci la dimensione:"<<std::endl;
      std::cin>>dim;
      std::cout<<"List"<<std::endl;
      std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
      std::cin>>tipo;
      switch(tipo){
        case 1:
        {
          std::cout<<"Intero"<<std::endl;

          List<int> list;

          for(uint i=0;i<dim;i++){
            list.InsertAtBack(randomInt());
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(list);
              break;
            case 2:
              list.Map(&MapPrint<int>,nullptr);
              break;
            case 3:
              Esiste(list);
              break;
            case 4:
              Sum(list);
              break;
            case 5:
              std::cout<<"2n per gli interi"<<std::endl;
              list.Map(&MapDouble, nullptr);
              break;
            case 6:
              Mod(list);
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 2:
        {
          std::cout<<"Float"<<std::endl;

          List<float> list;

          for(uint i=0;i<dim;i++){
            list.InsertAtBack(randomFloat());
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(list);
              break;
            case 2:
              list.Map(&MapPrint<float>,nullptr);
              break;
            case 3:
              Esiste(list);
              break;
            case 4:
              Prod(list);
              break;
            case 5:
              std::cout<<"n^2 per i float"<<std::endl;
              list.Map(&MapSquare, nullptr);
              break;
            case 6:
              Mod(list);
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 3:
        {
          std::cout<<"String"<<std::endl;

          List<std::string> list;

          for(uint i=0;i<dim;i++){
            list.InsertAtBack(randomString());
          }

          std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Visual(list);
              break;
            case 2:
              list.Map(&MapPrint<std::string>,nullptr);
              break;
            case 3:
              Esiste(list);
              break;
            case 4:
              Concat(list);
              break;
            case 5:
              std::cout<<"Uppercase per le stringhe"<<std::endl;
              list.Map(&MapUpper, nullptr);
              break;
            case 6:
              Mod(list);
              break;
            }

            std::cout<<"Operazioni\n1:Visualizza\n2:Map Print\n3:Exists\n4:Fold\n5:Map\n6:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
      }
      break;
    case 3:
      std::cout<<"Stack"<<std::endl;
      std::cout<<"Implementazione\n1:Vector\n2:List"<<std::endl;
      std::cin>>imp;

      switch(imp){
        case 1:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"StackVec"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;
              
              StackVec<int> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomInt());
              }

              menuStack(stack);

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;
              
              StackVec<float> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomFloat());
              }

              menuStack(stack);

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;
              
              StackVec<std::string> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomString());
              }

              menuStack(stack);

              break;
            }
          }
        break;
        case 2:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"StackList"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;
              
              StackLst<int> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomInt());
              }

              menuStack(stack);

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;
              
              StackLst<float> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomFloat());
              }

              menuStack(stack);

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;
              
              StackLst<std::string> stack;

              for(uint i=0;i<dim;i++){
                stack.Push(randomString());
              }

              menuStack(stack);

              break;
            }
          }
        break;
      }
    break;
    case 4:
      std::cout<<"Queue"<<std::endl;
      std::cout<<"Implementazione\n1:Vector\n2:List"<<std::endl;
      std::cin>>imp;

      switch(imp){
        case 1:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"QueueVec"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;

              QueueVec<int> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomInt());
              }

              menuQueue(queue);

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;
              
              QueueVec<float> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomFloat());
              }

              menuQueue(queue);

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;
              
              QueueVec<std::string> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomString());
              }

              menuQueue(queue);

              break;
            }
          }

        break;
        case 2:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"QueueList"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;
              
              QueueLst<int> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomInt());
              }

              menuQueue(queue);

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;
              
              QueueLst<float> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomFloat());
              }

              menuQueue(queue);

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;
              
              QueueLst<std::string> queue;

              for(uint i=0;i<dim;i++){
                queue.Enqueue(randomString());
              }

              menuQueue(queue);

              break;
            }
          }

        break;
      }
    break;
    case 5:
      std::cout<<"BinaryTree"<<std::endl;
      std::cout<<"Implementazione\n1:Vector\n2:List"<<std::endl;
      std::cin>>imp;

      switch(imp){
        case 1:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"BtVec"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;

              Vector<int> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomInt();
              }

              BinaryTreeVec<int> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Sum(tree);
                  break;
                case 4:
                  std::cout<<"3n per gli interi"<<std::endl;
                  tree.Map(&MapTriple, nullptr);
                  break;
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;

              Vector<float> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomFloat();
              }

              BinaryTreeVec<float> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Prod(tree);
                  break;
                case 4:
                  std::cout<<"n^3 per i float"<<std::endl;
                  tree.Map(&MapCube, nullptr);
                  break;
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;

              Vector<std::string> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomString();
              }

              BinaryTreeVec<std::string> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Concat(tree);
                  break;
                case 4:
                  {
                  std::cout<<"Concatenazione in testa per le stringhe"<<std::endl;
                  std::cout<<"Inserisci una stringa:"<<std::endl;
                  std::string str;
                  std::cin>>str;

                  tree.Map(&MapConcat, &str);
                  break;
                  } 
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
          }

        break;
        case 2:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"BtLst"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;

              Vector<int> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomInt();
              }

              BinaryTreeLnk<int> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Sum(tree);
                  break;
                case 4:
                  std::cout<<"3n per gli interi"<<std::endl;
                  tree.Map(&MapTriple, nullptr);
                  break;
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 2:
            {
              std::cout<<"Float"<<std::endl;

              Vector<float> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomFloat();
              }

              BinaryTreeLnk<float> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Prod(tree);
                  break;
                case 4:
                  std::cout<<"n^3 per i float"<<std::endl;
                  tree.Map(&MapCube, nullptr);
                  break;
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;

              Vector<std::string> vec(dim);

              for(uint i=0;i<vec.Size();i++){
                vec[i] = randomString();
              }

              BinaryTreeLnk<std::string> tree(vec);

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  Print(tree);
                  break;
                case 2:
                  Esiste(tree);
                  break;
                case 3:
                  Concat(tree);
                  break;
                case 4:
                  {
                  std::cout<<"Concatenazione in testa per le stringhe"<<std::endl;
                  std::cout<<"Inserisci una stringa:"<<std::endl;
                  std::string str;
                  std::cin>>str;

                  tree.Map(&MapConcat, &str);
                  break;
                  } 
                case 5:
                  menuNodo(tree);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Map\n5:Nodo\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
          }

        break;
      }
    break;
    case 6:
      std::cout<<"BinarySearchTree"<<std::endl;
      std::cout<<"Inserisci la dimensione:"<<std::endl;
      std::cin>>dim;
      std::cout<<"Tipo dato:\n1:Int\n2:Float\n3:String"<<std::endl;
      std::cin>>tipo;

      switch(tipo){
        case 1:
        {
          std::cout<<"Intero"<<std::endl;

          Vector<int> vec(dim);

          for(uint i=0;i<vec.Size();i++){
            vec[i] = randomInt();
          }

          BST<int> tree(vec);

          std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Print(tree);
              break;
            case 2:
              Esiste(tree);
              break;
            case 3:
              ProdInt(tree);
              break;
            case 4:
              menuBST(tree);
              break;
            }

            std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 2:
        {
          std::cout<<"Float"<<std::endl;

          Vector<float> vec(dim);

          for(uint i=0;i<vec.Size();i++){
            vec[i] = randomFloat();
          }

          BST<float> tree(vec);

          std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Print(tree);
              break;
            case 2:
              Esiste(tree);
              break;
            case 3:
              SumFloat(tree);
              break;
            case 4:
              menuBST(tree);
              break;
            }

            std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
        case 3:
        {
          std::cout<<"String"<<std::endl;

          Vector<std::string> vec(dim);

          for(uint i=0;i<vec.Size();i++){
            vec[i] = randomString();
          }

          BST<std::string> tree(vec);

          std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
          std::cin>>op;

          while(op != 0){
            switch(op){
            case 1:
              Print(tree);
              break;
            case 2:
              Esiste(tree);
              break;
            case 3:
              Concat(tree);
              break;
            case 4:
              menuBST(tree);
              break;
            }

            std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
            std::cin>>op;
          }

          break;
        }
      }
    break;
    case 7:
      std::cout<<"HashTable"<<std::endl;
      std::cout<<"Implementazione\n1:ClsAdr\n2:OpnAdr"<<std::endl;
      std::cin>>imp;

      switch(imp){
        case 1:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"ClsAdr"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Double\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;

              HashTableClsAdr<int> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomInt());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<int>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  ProdInt(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 2:
            {
              std::cout<<"Double"<<std::endl;

              HashTableClsAdr<double> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomDouble());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<double>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  SumDouble(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;

              HashTableClsAdr<std::string> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomString());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<std::string>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  Concat(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
          }

        break;
        case 2:
          std::cout<<"Inserisci la dimensione:"<<std::endl;
          std::cin>>dim;
          std::cout<<"OpnAdr"<<std::endl;
          std::cout<<"Tipo dato:\n1:Int\n2:Double\n3:String"<<std::endl;
          std::cin>>tipo;

          switch(tipo){
            case 1:
            {
              std::cout<<"Intero"<<std::endl;

              HashTableOpnAdr<int> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomInt());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<int>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  ProdInt(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 2:
            {
              std::cout<<"Double"<<std::endl;

              HashTableOpnAdr<double> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomDouble());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<double>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  SumDouble(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
            case 3:
            {
              std::cout<<"String"<<std::endl;

              HashTableOpnAdr<std::string> table(dim);

              for(uint i=0;i<dim;i++){
                table.Insert(randomString());
              }

              std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
              std::cin>>op;

              while(op != 0){
                switch(op){
                case 1:
                  table.Map(&MapPrint<std::string>,nullptr);
                  break;
                case 2:
                  Esiste(table);
                  break;
                case 3:
                  Concat(table);
                  break;
                case 4:
                  ModHash(table);
                  break;
                }

                std::cout<<"Operazioni\n1:Map Print\n2:Exists\n3:Fold\n4:Mod\n0:Exit"<<std::endl;
                std::cin>>op;
              }

              break;
            }
          }

        break;
      }
    break;
  }
}