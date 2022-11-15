#include <string>
#include <tuple>
#include <stack>

using  namespace  std;


template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const {
    if (empty()) {
        return 0;
    }
    Nodo *actual = raiz;
    for(int i = 0; i<clave.size(); i++){
        int posLetraVector = int(clave[i]);
        if(actual->siguientes[posLetraVector] == nullptr){
            return 0;
        }
        else{
            actual= actual->siguientes[posLetraVector];
            if(i == clave.size()-1){
                return int(actual->definicion != nullptr);
            }
        }
    }
}


template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
}


//la pre condición es que este definida la clave que quiero borrar
template<class T>
bool string_map<T>::noTieneSig(Nodo *a) {
    bool res = true;
    for (int i = 0; i < a->siguientes.size() ; ++i) {
        res &= (a->siguientes[i] == nullptr);
    }
    return res;
}

template<class T>
void string_map<T>::erase(const string& clave) {
    if(count(clave) != 1){
        cout << "ingresaste una clave que no está definida";
    }
    stack<Nodo*> letrasDeLaPalabra;
    //armar cola de letrasDeLaPalabra
    Nodo* actual = raiz;
    //van a llevar la cuenta de si borre, y cual fue el ultimo que borré
    bool borre = false;
    int posUltimoBorrado;
    letrasDeLaPalabra.push(actual);
    int i = 0;
    while(i<clave.size()){
        int posLetraVector = int(clave[i]);
        actual = actual->siguientes[posLetraVector];
        ++i;
    }   // acá lo que tengo es una pila con la raiz y las letras de la palabra
    for(int k = 0; k < letrasDeLaPalabra.size(); ++k){
        //caso en el que los nodos que borro no tienen hijos
        if(noTieneSig(letrasDeLaPalabra.top())){
            Nodo* aborrar = letrasDeLaPalabra.top();
            //delete aborrar->siguientes; al parecer no es necesario ya que es un vector de nullptr
            delete aborrar->definicion;
            letrasDeLaPalabra.pop();
            posUltimoBorrado = int(clave[clave.size()-(k+1)]);
            _size --;
            actual = letrasDeLaPalabra.top();
            actual->siguientes[posUltimoBorrado] = nullptr;
        }
        else if(not(noTieneSig(letrasDeLaPalabra.top()))){
            T* aBorrar = letrasDeLaPalabra.top()->definicion;
            letrasDeLaPalabra.top()->definicion = nullptr;
            delete aBorrar;
            _size --;
        }
    }
}

template <typename T>
int string_map<T>::size() const {
    return _size;
}

template <typename T> //el diccionario vacio tiene un nodo raiz cuyos Nodos siguientes son todos nulos.
bool string_map<T>::empty() const{
    bool res = true;
    for(Nodo* a : raiz->siguientes){
         res &= (a == nullptr);
    }
    return res;
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& value) {
    Nodo* actual = raiz;
    T* def = new T(value.second);
    string palabra = value.first;
    for(int i = 0; i< palabra.size();++i){
        int posLetraVector = palabra[i];
        if(i != palabra.size()-1){
            if(actual->siguientes[posLetraVector] == nullptr){
                actual->siguientes[posLetraVector]= new Nodo();
                actual = actual->siguientes[posLetraVector];
            }
            else{
                actual = actual->siguientes[posLetraVector];
            }
        }
        else{   //aca actual es el anterior al ultimo nodo => actual->siguientes[posLetraVector] es el ultimo nodo.
            if(actual->siguientes[posLetraVector] == nullptr){ //Si no está definido creo un nuevo nodo
                actual->siguientes[posLetraVector] = new Nodo(def);
                _size ++;
            }
            else{
                actual = actual->siguientes[posLetraVector];
                if(actual->definicion != nullptr){          //REDEFINO Y BORRO EL SIGNIFICADO ANTERIOR
                    T* aBorrar = actual->definicion;
                    actual->definicion = def;
                    delete aBorrar;
                }
                else{
                    actual->definicion = def;
                    _size++;
                }
            }
        }
    }
}