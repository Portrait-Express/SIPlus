%module(directors="1") siplusswig

%{
template<typename Type>
using simple_value_retrievable_type = false;

#include "include/siplus/parser.hxx"
#include "include/siplus/invocation_context.hxx"
#include "include/siplus/function.hxx"
#include "include/siplus/context.hxx"
#include "include/siplus/data.hxx"
#include "include/siplus/stl.hxx"

#include "include/siplus/text/constructor.hxx"
#include "include/siplus/text/converter.hxx"
#include "include/siplus/text/iterator.hxx"
#include "include/siplus/text/value_retrievers/retriever.hxx"

#include "include/siplus/types/array.hxx"
#include "include/siplus/types/bool.hxx"
#include "include/siplus/types/float.hxx"
#include "include/siplus/types/integer.hxx"
#include "include/siplus/types/string.hxx"
%}

%feature("director") Function;
%feature("director") Converter;
%feature("director") Iterator;

%include "include/siplus/parser.hxx"
%include "include/siplus/invocation_context.hxx"
%include "include/siplus/function.hxx"
%include "include/siplus/context.hxx"
%include "include/siplus/data.hxx"
%include "include/siplus/stl.hxx"

#include "include/siplus/text/constructor.hxx"
#include "include/siplus/text/converter.hxx"
#include "include/siplus/text/iterator.hxx"
%include "include/siplus/text/value_retrievers/retriever.hxx"

%include "include/siplus/types/array.hxx"
%include "include/siplus/types/bool.hxx"
%include "include/siplus/types/float.hxx"
%include "include/siplus/types/integer.hxx"
%include "include/siplus/types/string.hxx"
