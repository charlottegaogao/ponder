/****************************************************************************
 **
 ** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
 ** Contact: Tegesoft Information (contact@tegesoft.com)
 **
 ** This file is part of the CAMP library.
 **
 ** The MIT License (MIT)
 **
 ** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy
 ** of this software and associated documentation files (the "Software"), to deal
 ** in the Software without restriction, including without limitation the rights
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 ** copies of the Software, and to permit persons to whom the Software is
 ** furnished to do so, subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in
 ** all copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 ** THE SOFTWARE.
 **
 ****************************************************************************/


#ifndef CAMP_DICTIONARY_HPP
#define CAMP_DICTIONARY_HPP

#include <utility>
#include <vector>

namespace camp
{

template <typename KEY, typename VALUE, class CMP>
class Dictionary
{
    typedef std::pair<KEY,VALUE> pair;

    typedef std::vector<pair> Container;
    Container m_contents;
    
    struct KeyCmp {
        bool operator () (const pair& a, const KEY &b) const {
            return CMP() (a.first, b);
        }
    };

public:
    
    typedef typename Container::const_iterator const_iterator;
    
    const_iterator begin() const    { return m_contents.begin(); }
    const_iterator end() const      { return m_contents.end(); }

    typename Container::const_iterator find(const KEY &key) const
    {
        //typename Container::const_iterator it = std::lower_bound(m_contents.cbegin(), m_contents.cend(), key, KeyCmp());
//        return it;
        return std::find_if(m_contents.begin(), m_contents.end(), CMP());
    }

    bool tryFind(const KEY &key, const_iterator &returnValue) const
    {
        auto it = find(key);
        if (it != m_contents.end())
        {
            returnValue = it;
            return true;
        }
        return false; // not found
    }
    
    bool contains(const KEY &key) const
    {
        return find(key) != m_contents.end();
    }
    
    std::size_t size() const { return m_contents.size(); }

    void insert(const KEY &key, const VALUE &value)
    {
//        auto it = find(key);
//        m_contents.insert(it, pair(key,value));
        m_contents.push_back(pait(key,value));
    }
    
    void insert(const_iterator it)
    {
        insert(it->first, it->second);
    }
    
    void erase(const KEY &key)
    {
        auto it = find(key);
        if (it != m_contents.end())
            m_contents.erase(it);
    }
};
    
}

#endif // CAMP_DICTIONARY_HPP