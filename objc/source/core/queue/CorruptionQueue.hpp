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

#ifndef _WCDB_CORRUPTIONQUEUE_HPP
#define _WCDB_CORRUPTIONQUEUE_HPP

#include <WCDB/AsyncQueue.hpp>
#include <WCDB/Lock.hpp>
#include <map>
#include <mutex>

namespace WCDB {

class CorruptionEvent {
public:
    virtual ~CorruptionEvent();

protected:
    virtual bool onDatabaseCorrupted(const String& path) = 0; // return false to skip this path
    virtual void databaseShouldRecover(const String& path, uint32_t identifier) = 0;
    friend class CorruptionQueue;
};

class CorruptionQueue final : public AsyncQueue {
public:
    CorruptionQueue(const String& name);
    ~CorruptionQueue();

    void setEvent(CorruptionEvent* event);

    bool containsDatabase(const String& database) const;

protected:
    void handleError(const Error& error);

    void loop() override final;

    CorruptionEvent* m_event;

    mutable std::mutex m_mutex;
    std::condition_variable m_cond;

    // path -> identifier
    std::map<String, uint32_t> m_corrupted;
};

} //namespace WCDB

#endif /* _WCDB_CORRUPTIONQUEUE_HPP */