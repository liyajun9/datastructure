#ifndef DATASTRUCTURE_BINARY_HEAP_HPP
#define DATASTRUCTURE_BINARY_HEAP_HPP
#include <iostream>
#include <queue>
#include <algorithm>
#include <ext/pb_ds/detail/cond_dealtor.hpp>
#include <ext/pb_ds/detail/cond_dealtor.hpp>
#include <ext/pb_ds/detail/type_utils.hpp>
#include <ext/pb_ds/detail/binary_heap_/entry_cmp.hpp>
#include <ext/pb_ds/detail/binary_heap_/entry_pred.hpp>
#include <ext/pb_ds/detail/binary_heap_/resize_policy.hpp>
#include <ext/pb_ds/detail/binary_heap_/const_iterator.hpp>
#include <ext/pb_ds/detail/type_utils.hpp>
#include <debug/debug.h>

namespace lyj
{
//template declaration part of class declaration
#define PB_DS_CLASS_T_DEC \
    template<typename Value_Type, class Cmp_Fn, class Allocator>

//class declaration part of class declaration
#define PB_DS_CLASS_C_DEC \
    binary_heap<Value_Type, Cmp_fn, Allocator>

//entry compare declaration
#define PB_DS_ENTRY_CMP_DEC \
    entry_cmp<Value_Type, Cmp_Fn, is_simple<Value_Type>::value, Allocator>::type

//resize policy declaration
#define PB_DS_RESIZE_POLICY_DEC \
    __gnu_pbds::detail::resize_policy<typename Allocator::size_type>

//    template<typename Value_Type, class Cmp_Fn, class Allocator>
//    class binary_heap : public PB_DS_ENTRY_CMP_DEC, public PB_DS_RESIZE_POLICY_DEC
//    {
//
//    };
}




#endif //DATASTRUCTURE_BINARY_HEAP_HPP
