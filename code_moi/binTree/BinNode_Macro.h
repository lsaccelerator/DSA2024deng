#pragma once

#define IsRoot(x)(!((x).parent))
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

#define sibling(x) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) //返回p的兄弟
#define uncle( x ) ( sibling( (x)->parent ) ) 
#define FromParentTo( x ) /*来自父亲的引用，返回从父结点指向x的指针*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )