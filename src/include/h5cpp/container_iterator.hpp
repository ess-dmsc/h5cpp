//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 24, 2017
//
#pragma once

#include <stdexcept>

namespace hdf5{


    //! 

    //! \brief iterator type
    //! 
    //! This is the most generic iterator provided by libpnicore. It can be 
    //! used with all container types provided by the library. A container 
    //! that wants to use this iterator must implement the following 
    //! interface
    /*!
    \code
    template<typename T> class Iterable<T>
    {
        public:
            typedef T value_type;
            size_t size() const;
            T &operator[](size_t i);
            T operator[](size_t i) const;
    };
    \endcode
    !*/ 
    //! This template implements a simple forward iterator. Unlike STL 
    //! iterators an exception is thrown if one tries to dereference an invalid 
    //! iterator
    //! 
    //! \tparam ITERABLE iterable type 
    //!
    template<typename ITERABLE> class ContainerIterator
    {
        private:
            //! type of the container object
            typedef typename std::remove_const<ITERABLE>::type container_type;
            //! pointer type of the container
            typedef ITERABLE *cptr_type;
            //! pointer to the container object
            ITERABLE *_container; 

            //! actual position state of the iterator
            ssize_t _state;                    

            //! maximum number of elements in the container
            ssize_t _maxsize;

        public:
            //====================public types==================================
            //! value type of the container
            typedef typename container_type::value_type value_type;
            //! pointer type the iterator provides
            typedef typename std::conditional<std::is_const<ITERABLE>::value,
                                             const value_type*,value_type*>::type pointer;
            //! reference type the iterator provides
            typedef typename std::conditional<std::is_const<ITERABLE>::value,
                                              const value_type&,value_type&>::type reference;
            //! difference type of the iterator
            typedef ssize_t difference_type;
            //! type of iterator
            typedef std::random_access_iterator_tag iterator_category;
            //! iterator type
            typedef container_iterator<ITERABLE> iterator_type;
            //================constructor and destructor========================
            //! default constructor
            ContainerIterator():_container(nullptr),_state(0),_maxsize(0) {}

            //------------------------------------------------------------------
            //! \brief constructor
            //!
            //! This constructor takes a pointer to the container and an 
            //! initial position.
            //! 
            //! \param container pointer to the container object
            //! \param state initial position of the iterator
            //!
            explicit ContainerIterator(cptr_type container,size_t state=0):
                _container(container),
                _state(state),
                _maxsize(container->size())
            { }

            //------------------------------------------------------------------
            //! copy constructor
            ContainerIterator(const iterator_type &i):
                _container(i._container),
                _state(i._state),
                _maxsize(i._maxsize)
            { }

            //------------------------------------------------------------------
            //! move constructor
            ContainerIterator(iterator_type &&i):
                _container(i._container),
                _state(i._state),
                _maxsize(i._maxsize)
            {
                i._container = nullptr;
                i._state = 0;
                i._maxsize = 0;
            }

            //------------------------------------------------------------------
            //! default constructor
            ~ContainerIterator() {}

            //=================assignment operator==============================
            //! copy assignment operator
            iterator_type &operator=(const iterator_type &i)
            {
                if(this == &i) return *this;
                _container = i._container;
                _state     = i._state;
                _maxsize   = i._maxsize;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            iterator_type &operator=(iterator_type &&i)
            {
                if(this == &i) return *this;
                _container = i._container;
                i._container = nullptr;
                _state = i._state;
                i._state = 0;
                _maxsize = i._maxsize;
                i._maxsize = 0;
                return *this;
            }

            //====================public methods and operators==================
            //! 
            //! \brief conversion operator
            //!
            //! This operator allows the conversion of an iterator to bool. It 
            //! will return true if the iterator is valid and false otherwise.
            //! The iterator is consideres as invalid if its internal state is 
            //! at least one after the last element or smaller than 0. It is 
            //! important that this conversion operator is set \c explicit. 
            //! Otherwise the iterator would be implicitly convertible to 
            //! integer (via bool).
            //! 
            //! \return boolean value
            //!
            explicit operator bool() const
            {
                return !( (!_container)|| (_state >= _maxsize)|| (_state<0));
            }
            
            //------------------------------------------------------------------
            //! 
            //! \brief dereferencing operator
            //!
            //! Returns a reference on the object the iterator is actually 
            //! pointer or the object by value. The return type depends if the 
            //! iterator is used as a standard iterator or a const iterator.
            //!
            //! \throws IteratorError if the iterator is invalid
            //! \return reference or value of the actual object
            //!
            typename std::conditional<std::is_const<ITERABLE>::value,
                                      value_type,reference>::type
            operator*()
            {
                if(!(*this))
                    throw std::runtime_error("Iterator invalid!");

                return (*(_container))[_state];
            }
            
            //------------------------------------------------------------------
            //! 
            //! \brief const dereferencing operator
            //!
            //! In this case the iterator always returns a value_type with a 
            //! copy of the original object.
            //!
            //! \throws IteratorError if the iterator is invalid
            //! \return reference or value of the actual object
            //!
            value_type operator*() const
            {
                if(!(*this))
                    throw std::runtime_error("Iterator invalid!");

                return (*(_container))[_state];
            }


            //------------------------------------------------------------------
            //!
            //! \brief pointer access operator
            //!
            //! Returns a const or non-const pointer to the object the iterator
            //! actually points to. 
            //!
            //! \throws IteratorError if the iterator is invalid
            //! \return pointer to actual object
            //!
            pointer operator->()
            {
                if(!(*this))
                    throw std::runtime_error("Iterator invalid!");

                return &(*(_container))[_state];
            }

            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type &operator++()
            {
                _state++;
                return *this;
            }

            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type operator++(int)
            {
                iterator_type temp = *this;
                ++(*this);
                return temp;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type &operator--()
            {
                _state--;
                return *this;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type operator--(int)
            {
                iterator_type tmp = *this;
                --(*this);
                return tmp;
            }

            //------------------------------------------------------------------
            //! compound assignment with +=
            iterator_type &operator+=(ssize_t i)
            {
                _state += i;
                return *this;
            }

            //------------------------------------------------------------------
            //! compound assignment with -=
            iterator_type &operator-=(ssize_t i)
            {
                _state -= i;
                return *this;
            }
            //------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const iterator_type &a) const 
            {
                //check if the iterators point to the same container
                if(_container != a._container) return false;
                //check if the iterators point to the same element
                //within the container
                if(_state != a._state) return false;

                return true;
            }

            //------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const iterator_type &a) const
            {
                if((*this)==a) return false;
                return true;
            }

            //===============comparison operators==============================
            //! lesser than operator
            bool operator<(const iterator_type &b) const
            {
                return _state < b._state;
            }

            //-----------------------------------------------------------------
            //! lesser than equal operator
            bool operator<=(const iterator_type &b) const
            {
                return _state <= b._state;
            }

            //-----------------------------------------------------------------
            //! greater than operator
            bool operator>(const iterator_type &b) const
            {
                return _state > b._state;
            }

            //-----------------------------------------------------------------
            //! greater equal than operator
            bool operator>=(const iterator_type &b) const
            {
                return _state >= b._state;
            }

            //! get state of the iterator
            ssize_t state() const { return _state; }

    };

    //================binary arithmetic operators===============================
    //! 
    //! \brief add scalar to iterator
    //! 
    //! Add an offset to the iterator and thus increment its internal state by 
    //! this offset.
    //! 
    //! \code
    //! Iteartor<...> iter = ...'
    //! Iteartor<...> iter2 = iter+2;
    //! \endcode
    //! 
    //! \tparam ITER iterable type
    //! \param a original iterator
    //! \param b offset to add
    //! \return new iterator 
    //!
    template<typename ITER> 
    ContainerIterator<ITER> operator+(const ContainerIterator<ITER> &a,
                                       ssize_t b)
    {
        ContainerIterator<ITER> iter = a;
        iter += b;
        return iter;
    }

    //--------------------------------------------------------------------------
    //!
    //! \brief add offset to iterator
    //! 
    //! Add an offset to the iterator and thus increment its internal state by 
    //! this offset.
    //! 
    //! \tparam ITER iterable type
    //! \param a offset to add
    //! \param b original iterator
    //! \return new iterator
    //!
    template<typename ITER> 
    ContainerIterator<ITER> operator+(ssize_t a,
                                       const ContainerIterator<ITER> &b)
    {
        return b+a;
    }

    //--------------------------------------------------------------------------
    //!
    //! \brief subtract offset from iterator
    //!
    //! Subtract an integer offset from the iterator and thus decrement the 
    //! internal state of the iterator by this value. 
    //!
    //! \tparam ITER iterable type
    //! \param a original iterator
    //! \param b offset
    //! \return new iterator to new position
    //!
    template<typename ITER> 
    ContainerIterator<ITER> operator-(const ContainerIterator<ITER> &a,
                                       ssize_t b)
    {
        ContainerIterator<ITER> iter = a;
        iter -= b;
        return iter;
    }

    //--------------------------------------------------------------------------
    //!
    //! \brief subtract two iterators
    //! 
    //! Subtract to iterators and return the offset difference between this
    //! two iterators.
    //!
    //! \tparam ITER iterable type
    //! \param a first iterator
    //! \param b second iterator
    //! \return offset difference
    //!
    template<typename ITER> 
    ssize_t operator-(const ContainerIterator<ITER> &a,
                      const ContainerIterator<ITER> &b)
    {
        return a.state() - b.state();
    }

} // namespace hdf5
