#pragma once

template<typename T>
class DynamicVector {
private:
    T* elems;
    int size;
    int capacity;

public:
    /// <summary>
    /// default constructor for a DynamicVector
    /// </summary>
    /// <param name="capacity">The initial capactiry of the dynamic vector</param>
    DynamicVector(int capacity = 10);

    /// <summary>
    /// copy constructor for a DynamicVector
    /// </summary>
    /// <param name="v">The isntance of the DynamicVector</param>
    DynamicVector(const DynamicVector& v);

    /// Destructor of the dynamic vector
    ~DynamicVector();

    /// <summary>
    /// assignment operator for a DynamicVector
    /// </summary>
    /// <param name="v">Instance of the dynamic vector</param>
    /// <returns>A new dynamic vector instance copy (deepcopy)</returns>
    DynamicVector& operator=(const DynamicVector& v);

    /*
        Overloading the subscript operator
        Input: pos - a valid position within the vector.
        Output: a reference to the element o position pos.
    */
    T& operator[](int pos);

    /// <summary>
    /// Adds an element to the current DynamicVector.
    /// </summary>
    /// <param name="e">Instace of the element</param>
    void add(T e);

    /// <summary>
    /// deletes the element on the given position
    /// </summary>
    /// <param name="pos">The position of the element to be deleted</param>
    void deleteElementByIndex(int pos);

    /// <summary>
    /// updates the element from the given position with the new element
    /// </summary>
    /// <param name="new_elem">The new instance of the element</param>
    /// <param name="pos">The poition to be updated</param>
    void updateElement(T new_elem, int pos);

    /// <summary>
    /// Gets the index of the given element from the array (-1 if it wasnt found)
    /// </summary>
    /// <param name="elem">The element to be searched for</param>
    /// <returns>Integer representing the index found, or -1 if it wasnt found</returns>
    int getIndexOfElement(T elem);

    /// <summary>
    /// gets the whole array and returns it back
    /// </summary>
    /// <returns>Returns the array of elements</returns>
    T* getAllElements() { return this->elems; }

    /// <summary>
    /// returns the size of the array of elements
    /// </summary>
    /// <returns>Integer represeting the size of the dynamic vector</returns>
    int getSize() const;


private:
    /// <summary>
    /// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    /// </summary>
    /// <param name="factor">The factor with which the capacity will be multiplied</param>
    void resize(double factor = 2);
};

/// <summary>
/// default constructor for a DynamicVector
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="capacity">The initial capactiry of the dynamic vector</param>
template<typename T>
DynamicVector<T>::DynamicVector(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->elems = new T[capacity];
}

/// <summary>
/// copy constructor for a DynamicVector
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="v">The isntance of the DynamicVector</param>
template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v) {
    this->capacity = v.capacity;
    this->size = 0;
    this->elems = new T[this->capacity];
    int i = 0;
    for (i = 0;i< v.size;i++)
        this->add(v.elems[i]);
}

/// Destructor of the dynamic vector
template<typename T>
DynamicVector<T>::~DynamicVector() {
    /*int i = 0;
    for (i = 0; i < this->size; i++)
        delete this[i];*/

    delete[] this->elems;
}

/// <summary>
/// assignment operator for a DynamicVector
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="v">Instance of the dynamic vector</param>
/// <returns>A new dynamic vector instance copy (deepcopy)</returns>
template<typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v) {
    this->size = 0;
    int i = 0;
    for (i = 0; i < v.size; i++)
        this->add(v.elems[i]);

    return *this;
}

/*
    Overloading the subscript operator
    Input: pos - a valid position within the vector.
    Output: a reference to the element o position pos.
*/
template<typename T>
T& DynamicVector<T>::operator[](int pos) {
    
    if(pos < 0 || pos >= this->size)
        throw("Index out of range");

    return this->elems[pos];
}

/// <summary>
/// Adds an element to the current DynamicVector.
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="e">Instace of the element</param>
template<typename T>
void DynamicVector<T>::add(T e) {
    T new_e = e;
    
    if (this->size == this->capacity)
        this->resize();

    this->elems[this->size] = e;
    this->size++;
}

/// <summary>
/// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="factor">The factor with which the capacity will be multiplied</param>
template<typename T>
void DynamicVector<T>::resize(double factor) {
    this->capacity = this->capacity * factor;
    T* new_elems = new T[this->capacity];

    int i = 0;
    for (i = 0; i < this->size; i++)
    {
        new_elems[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = new_elems;
}

template<typename T>
int DynamicVector<T>::getSize() const {
    return this->size;
}

/// <summary>
/// deletes the element on the given position
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="pos">The position of the element to be deleted</param>
template<typename T>
void DynamicVector<T>::deleteElementByIndex(int pos) {
    if (pos < 0 || pos > this->size)
        throw("Index out of range.");

    for (int i = pos; i < this->size-1; i++)
    {
        this->elems[i] = this->elems[i + 1];
    }


    this->size--;
}

/// <summary>
/// updates the element from the given position with the new element
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="new_elem">The new instance of the element</param>
/// <param name="pos">The poition to be updated</param>
template<typename T>
void DynamicVector<T>::updateElement(T new_elem, int pos) {
   if (pos < 0 || pos > this->size)
       throw("Index out of range.");

   this->elems[pos] = new_elem;
}

/// <summary>
/// Gets the index of the given element from the array (-1 if it wasnt found)
/// </summary>
/// <typeparam name="T">Generic variable</typeparam>
/// <param name="elem">The element to be searched for</param>
/// <returns>Integer representing the index found, or -1 if it wasnt found</returns>
template<typename T>
int DynamicVector<T>::getIndexOfElement(T elem){
    for (int i = 0; i < this->size; i++) {
        if (this->elems[i] == elem)
            return i;
    }
    return -1;
}

