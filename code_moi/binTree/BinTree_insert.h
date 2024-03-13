
#pragma once

template <typename T> BinNodePosi<T> BinTree<T>::insert( T const& e )
   { _size = 1; return _root = new BinNode<T>( e ); } 

template <typename T> BinNodePosi<T> BinTree<T>::insert( T const& e, BinNodePosi<T> x )
   { _size++; x->insertAsLC( e ); updateHeightAbove( x ); return x->lc; } 

template <typename T> BinNodePosi<T> BinTree<T>::insert( BinNodePosi<T> x, T const& e )
   { _size++; x->insertAsRC( e ); updateHeightAbove( x ); return x->rc; } 