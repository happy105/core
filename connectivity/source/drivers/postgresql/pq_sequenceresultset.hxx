/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 *  Effective License of whole file:
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 *  Parts "Copyright by Sun Microsystems, Inc" prior to August 2011:
 *
 *    The Contents of this file are made available subject to the terms of
 *    the GNU Lesser General Public License Version 2.1
 *
 *    Copyright: 2000 by Sun Microsystems, Inc.
 *
 *    Contributor(s): Joerg Budischewski
 *
 *  All parts contributed on or after August 2011:
 *
 *    This Source Code Form is subject to the terms of the Mozilla Public
 *    License, v. 2.0. If a copy of the MPL was not distributed with this
 *    file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ************************************************************************/

#ifndef INCLUDED_CONNECTIVITY_SOURCE_DRIVERS_POSTGRESQL_PQ_SEQUENCERESULTSET_HXX
#define INCLUDED_CONNECTIVITY_SOURCE_DRIVERS_POSTGRESQL_PQ_SEQUENCERESULTSET_HXX

#include <cppuhelper/propshlp.hxx>
#include <cppuhelper/component.hxx>

#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/sdbc/XCloseable.hpp>
#include <com/sun/star/sdbc/XColumnLocate.hpp>
#include "pq_connection.hxx"
#include "pq_baseresultset.hxx"
#include "pq_statics.hxx"

namespace pq_sdbc_driver
{

class SequenceResultSet : public BaseResultSet
{
protected:
    std::vector< std::vector< css::uno::Any > > m_data;

    std::vector< OUString > m_columnNames;
    css::uno::Reference< css::sdbc::XResultSetMetaData > m_meta;

protected:
    /** mutex should be locked before called
     */
    virtual void checkClosed()
        throw ( css::sdbc::SQLException, css::uno::RuntimeException ) override;

    /** unchecked, acquire mutex before calling
     */
    virtual css::uno::Any getValue( sal_Int32 columnIndex ) override;

public:
    SequenceResultSet(
        const ::rtl::Reference< RefCountedMutex > & mutex,
        const css::uno::Reference< css::uno::XInterface > &owner,
        const std::vector< OUString > &colNames,
        const std::vector< std::vector< css::uno::Any > > &data,
        const css::uno::Reference< css::script::XTypeConverter > &tc,
        const ColumnMetaDataVector *pVec = nullptr);
    virtual ~SequenceResultSet();

public: // XCloseable
    virtual void SAL_CALL close(  )
        throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;

public: // XResultSetMetaDataSupplier
    virtual css::uno::Reference< css::sdbc::XResultSetMetaData > SAL_CALL getMetaData(  )
        throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;

public: // XColumnLocate
    virtual sal_Int32 SAL_CALL findColumn( const OUString& columnName )
        throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
};

}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
