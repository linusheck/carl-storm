/**
 * Common.h
 * @author Florian Corzilius<corzilius@cs.rwth-aachen.de>
 * @since 2013-10-07
 * @version 2014-10-30
 */

#pragma once

#include <vector>
#include <set>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include "../core/logging.h"
#include "../core/MultivariatePolynomial.h"
#include "../core/Variable.h"
#include "../core/VariablePool.h"
#include "../interval/Interval.h"
#include "../interval/IntervalEvaluation.h"
#include "../interval/Contraction.h"
#include "../io/streamingOperators.h"

namespace carl
{

    // Enumerations.
    /// @todo Are these enumerations needed in carl or should we put them to smtrat?
    enum class Variable_Domain: unsigned { BOOLEAN = 0, REAL = 1, INTEGER = 2 };
    
    enum class Logic : unsigned { UNDEFINED, QF_NRA, QF_LRA, QF_NIA, QF_LIA };
	inline std::ostream& operator<<(std::ostream& os, const Logic& l) {
	switch (l) {
		case Logic::UNDEFINED:	os << "undefined"; break;
		case Logic::QF_NRA:		os << "QF_NRA"; break;
		case Logic::QF_LRA:		os << "QF_LRA"; break;
		case Logic::QF_NIA:		os << "QF_NIA"; break;
		case Logic::QF_LIA:		os << "QF_LIA"; break;
	}
	return os;
}
    
    /// @todo Is this enumerations needed in carl or should we put them to smtrat?
    ///An enum with the possible answer a Module can give
    enum Answer { True = 0, False = 1, Unknown = 2 };
    
    // Structures.
    
    template<typename T> 
    struct pointerEqual
    {
        bool operator()( const T* _argA, const T* _argB ) const
        {
            return (*_argA)==(*_argB);
        }
    };
    
    template<typename T> 
    struct pointerEqualWithNull
    {
        bool operator()( const T* _argA, const T* _argB ) const
        {
            if( _argA == NULL || _argB == NULL )
                return _argA == _argB;
            return (*_argA)==(*_argB);
        }
    };
    
    template<typename T> 
    struct pointerLess
    {
        bool operator()( const T* _argA, const T* _argB ) const
        {
            return (*_argA)<(*_argB);
        }
    };

    template<typename T> 
    struct pointerHash
    {
        size_t operator()( const T* _arg ) const
        {
            return std::hash<T>()( *_arg );
        }
    };

    template<typename T> 
    struct pointerHashWithNull
    {
        size_t operator()( const T* _arg ) const
        {
            if( _arg == NULL )
                return 0;
            return std::hash<T>()( *_arg );
        }
    };
    
    // Further type definitions.
    template<typename T> 
    using EvaluationMap = std::map<Variable, T>;
    
    template<typename Polynomial>
    using VarInfo = VariableInformation<true, Polynomial>;
    
    template<typename Polynomial>
    using VarInfoMap = std::map<Variable, VarInfo<Polynomial>>;
    
    typedef std::set<Variable> Variables;

	typedef std::vector<Variables> QuantifiedVariables;
    
    template<typename T> 
    using PointerSet = std::set<const T*, pointerLess<T>>;
    
    template<typename T> 
    using PointerMultiSet = std::multiset<const T*, pointerLess<T>>;
    
    template<typename T1,typename T2> 
    using PointerMap = std::map<const T1*, T2, pointerLess<T1>>;
    
    template<typename T> 
    using FastSet = std::unordered_set<const T, std::hash<T>>;
    
    template<typename T1,typename T2> 
    using FastMap = std::unordered_map<const T1, T2, std::hash<T1>>;
    
    template<typename T> 
    using FastPointerSet = std::unordered_set<const T*, pointerHash<T>, pointerEqual<T>>;
    
    template<typename T1,typename T2> 
    using FastPointerMap = std::unordered_map<const T1*, T2, pointerHash<T1>, pointerEqual<T1>>;
    
    template<typename T> 
    using FastPointerSetB = std::unordered_set<const T*, pointerHashWithNull<T>, pointerEqualWithNull<T>>;
    
    template<typename T1,typename T2> 
    using FastPointerMapB = std::unordered_map<const T1*, T2, pointerHashWithNull<T1>, pointerEqualWithNull<T1>>;
    
    template<typename Polynomial>
    using Factors = FastMap<Polynomial,unsigned>;
    
    template<template<typename> class Operator, typename Polynomial>
    using Contractor = Contraction<Operator, Polynomial>;
    
    // Constants.
    ///@todo move static variables to own cpp
    
    static const unsigned MAX_DEGREE_FOR_FACTORIZATION = 6;
    
    static const unsigned MIN_DEGREE_FOR_FACTORIZATION = 2;
    
    static const unsigned MAX_DIMENSION_FOR_FACTORIZATION = 6;
    
    static const unsigned MAX_NUMBER_OF_MONOMIALS_FOR_FACTORIZATION = 7;
    
    // Macros.

    #define CIRCULAR_SHIFT(_intType, _value, _shift) ((_value << _shift) | (_value >> (sizeof(_intType)*8 - _shift)))
    
}    // namespace carl




