///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-01-19
// Updated : 2010-01-19
// Licence : This source is under MIT License
// File    : gli/operator.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_OPERATOR_INCLUDED
#define GLI_OPERATOR_INCLUDED

#include "image.hpp"

namespace gli{
namespace detail
{

}//namespace detail

	image operator+(image const & ImageA, image const & ImageB);
	image operator-(image const & ImageA, image const & ImageB);

}//namespace gli

#include "operator.inl"

#endif//GLI_OPERATOR_INCLUDED
