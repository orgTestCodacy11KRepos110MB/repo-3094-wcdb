/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _WCDB_MIGRATION_HPP
#define _WCDB_MIGRATION_HPP

#include <WCDB/MigrationInfo.hpp>
#include <functional>
#include <map>
#include <set>

namespace WCDB {

// There are two ways to set up Migration. Set the user info for those existing tables or set a filter.
class Migration final {
#pragma mark - Initialize
public:
    Migration();

    class Initializer {
    public:
        virtual ~Initializer();

        virtual const String& getDatabasePath() const = 0;

        virtual std::pair<bool, std::set<String>> getTables() = 0;
        // When succeed, the empty column means that table does not exist.
        virtual std::pair<bool, std::set<String>>
        getColumns(const String& table, const String& database) = 0;

        virtual void setError(const Error& error) = 0;
        virtual const Error& getError() const = 0;
    };
    // Resolve user infos and get the column names of origin table
    bool initialize(Initializer& initializer);
    bool isInitialized() const;

protected:
    void onStateChanged();
    bool m_initialized;

#pragma mark - Filter
public:
    typedef std::function<void(MigrationUserInfo&)> TableFilter;
    void filterTable(const TableFilter& tableFilter);

protected:
    TableFilter m_tableFilter;

#pragma mark - Infos
public:
    bool shouldMigrate() const;
    void markInfoAsMigrated(const MigrationInfo* info);

    const std::set<const MigrationInfo*>& getMigratingInfos() const;

protected:
    std::set<const MigrationInfo*> m_migrating;

    std::map<String, const MigrationInfo> m_holder; // infos will never be deleted.
};

} // namespace WCDB

#endif /* _WCDB_MIGRATION_HPP */