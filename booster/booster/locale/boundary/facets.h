//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOSTER_LOCALE_BOUNDARY_FACETS_H_INCLUDED
#define BOOSTER_LOCALE_BOUNDARY_FACETS_H_INCLUDED

#include <booster/config.h>
#include <booster/locale/boundary/types.h>
#ifdef BOOSTER_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <vector>




namespace booster {

    namespace locale {
        
        ///
        /// \brief This namespae contains all operations required for boundary analysis of text
        ///
        namespace boundary {
            ///
            /// \addtogroup boundary
            ///
            /// @{
            ///

            
            ///
            /// This structure is used for representing boundary point
            /// that follows the offset.
            ///
            struct break_info {

                ///
                /// Create empty break point at beginning
                ///
                break_info() : 
                    offset(0),
                    rule(0)
                {
                }
                ///
                /// Create empty break point at offset v.
                /// it is useful for order comparison with other points.
                ///
                break_info(size_t v) :
                    offset(v),
                    rule(0)
                {
                }

                ///
                /// Offset from the beggining of the text where a break occurs.
                ///
                size_t offset;
                ///
                /// The identification of this break point according to 
                /// various break types
                ///
                rule_type rule;
               
                ///
                /// Compare two break points' offset. Allows to search with
                /// standard algorithms over the index.
                ///
                bool operator<(break_info const &other) const
                {
                    return offset < other.offset;
                }
            };
            
            ///
            /// This type holds the alalisys of the text - all its break points
            /// with marks
            ///
            typedef std::vector<break_info> index_type;


            template<typename CharType>
            class boundary_indexing;

            ///
            /// The facet that allows us to create an index for boundary analisys
            /// of the text.
            ///
            template<>
            class BOOSTER_API boundary_indexing<char> : public std::locale::facet {
            public:
                ///
                /// Default constructor typical for facets
                ///
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                ///
                /// Create index for boundary type \a t for text in range [begin,end)
                ///
                virtual index_type map(boundary_type t,char const *begin,char const *end) const = 0;
                /// Identification of this facet
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            
            ///
            /// The facet that allows us to create an index for boundary analisys
            /// of the text.
            ///
            template<>
            class BOOSTER_API boundary_indexing<wchar_t> : public std::locale::facet {
            public:
                ///
                /// Default constructor typical for facets
                ///
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                ///
                /// Create index for boundary type \a t for text in range [begin,end)
                ///
                virtual index_type map(boundary_type t,wchar_t const *begin,wchar_t const *end) const = 0;

                /// Identification of this facet
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            
            #ifdef BOOSTER_HAS_CHAR16_T
            template<>
            class BOOSTER_API boundary_indexing<char16_t> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,char16_t const *begin,char16_t const *end) const = 0;
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            #endif
            
            #ifdef BOOSTER_HAS_CHAR32_T
            template<>
            class BOOSTER_API boundary_indexing<char32_t> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,char32_t const *begin,char32_t const *end) const = 0;
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            #endif

            ///
            /// @}
            ///


        } // boundary

    } // locale
} // boost


#ifdef BOOSTER_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4