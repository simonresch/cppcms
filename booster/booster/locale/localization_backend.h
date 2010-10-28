//
//  Copyright (c) 2009-2010 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOSTER_LOCALE_LOCALIZATION_BACKEND_HPP
#define BOOSTER_LOCALE_LOCALIZATION_BACKEND_HPP
#include <booster/config.h>
#include <booster/locale/generator.h>
#ifdef BOOSTER_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <string>
#include <locale>
#include <vector>

namespace booster {
    namespace locale {

        ///
        /// \brief this class represents localization backend that can be used for localizing your application.
        /// 
        /// Backends are usually registered inside localization backends manager and allow transparent support
        /// of different backends, so user can swithc backend by simply linking the application to correct one.
        ///
        /// Backends may support different tuning options, but these are the default options avalible for user
        /// for all of them
        ///
        /// -# locale - the name of the locale in POSIX format like en_US.UTF-8
        /// -# message_path - path to location of message catalogs vector of strings
        /// -# message_application - the name of applications that use message catalogs (vector of strings)
        /// 
        /// Each backend may be installed with different default priority so when you work with two differnt backends, you
        /// can specify priotiry so this backend will be chosen according to their priority.
        ///
        
        class localization_backend {
            localization_backend(localization_backend const &);
            void operator=(localization_backend const &);
        public:

            localization_backend()
            {
            }
            
            virtual ~localization_backend()
            {
            }

            ///
            /// Make a polymorphic copy of the backend
            ///
            virtual localization_backend *clone() const = 0;

            ///
            /// Set option for backend, for example "locale" or "encoding"
            ///
            virtual void set_option(std::string const &name,std::string const &value) = 0;

            ///
            /// Clear all options
            ///
            virtual void clear_options() = 0;

            ///
            /// Create a facet for category \a category and character type \a type 
            ///
            virtual std::locale install(std::locale const &base,locale_category_type category,character_facet_type type = nochar_facet) = 0;

        }; // localization_backend 


        ///
        /// \brief Localization backend manager is a class that holds various backend and allows creation
        /// of their combination or selection
        ///

        class BOOSTER_API localization_backend_manager {
        public:
            ///
            /// New empty localization_backend_manager 
            ///
            localization_backend_manager();
            ///
            /// Copy localization_backend_manager 
            ///
            localization_backend_manager(localization_backend_manager const &);
            ///
            /// Assign localization_backend_manager 
            ///
            localization_backend_manager const &operator=(localization_backend_manager const &);

            ///
            /// Destructor
            ///
            ~localization_backend_manager();

            ///
            /// Create new localization backend according to current settings.
            ///
            std::auto_ptr<localization_backend> get() const;

            ///
            /// Add new backend to the manager, each backend should be uniquely defined by its name.
            ///
            /// This library provides: "icu", "posix", "winapi" and "std" backends.
            ///
            void add_backend(std::string const &name,std::auto_ptr<localization_backend> backend);

            ///
            /// Clear backend
            ///
            void remove_all_backends();
            
            ///
            /// Get list of all avalible backends
            ///
            std::vector<std::string> get_all_backends() const;
            
            ///
            /// Select specific backend by name for a category \a category. It allows combing different
            /// backends for user preferences.
            ///
            void select(std::string const &backend_name,locale_category_type category = all_categories);
           
            ///
            /// Set new global backend manager, the old one is returned.
            ///
            /// This function is thread safe
            /// 
            static localization_backend_manager global(localization_backend_manager const &);
            ///
            /// Get global backend manager
            ///
            /// This function is thread safe
            /// 
            static localization_backend_manager global();
        private:
            class impl;
            std::auto_ptr<impl> pimpl_;
        };

    } // locale
} // boost


#ifdef BOOSTER_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4 
