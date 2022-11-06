//
// Created by 陈秋文 on 2022/4/3.
//

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

#include <WCDB/AbstractHandle.hpp>
#include <WCDB/HandleStatementBridge.h>
#include <WCDB/InnerHandleStatement.hpp>
#include <WCDB/ObjectBridge.hpp>
#include <WCDB/UnsafeData.hpp>

CPPError WCDBHandleStatementGetError(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, CPPError());
    WCDB::AbstractHandle* cppHandle = cppHandleStatement->getHandle();
    if (!cppHandle) {
        return CPPError();
    }
    const WCDB::Error& error = cppHandle->getError();
    return WCDBCreateUnmanageCPPObject(CPPError, &error);
}

bool WCDBHandleStatementPrepare(CPPHandleStatement handleStatement, CPPStatement statement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, false);
    WCDBGetObjectOrReturnValue(statement, WCDB::Statement, cppStatement, true);
    return cppHandleStatement->prepare(*cppStatement);
}

bool WCDBHandleStatementCheckPrepared(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, false);
    return cppHandleStatement->isPrepared();
}

bool WCDBHandleStatementStep(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, false);
    return cppHandleStatement->step();
}

void WCDBHandleStatementReset(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->reset();
}

void WCDBHandleStatementFinalize(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->finalize();
}

bool WCDBHandleStatementIsDone(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, true);
    return cppHandleStatement->done();
}

void WCDBHandleStatementBindInteger(CPPHandleStatement handleStatement,
                                    int index,
                                    signed long long intValue)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->bindInteger(intValue, index);
}

void WCDBHandleStatementBindDouble(CPPHandleStatement handleStatement, int index, double doubleValue)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->bindDouble(doubleValue, index);
}

void WCDBHandleStatementBindText(CPPHandleStatement handleStatement, int index, const char* _Nonnull text)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->bindText(WCDB::UnsafeStringView(text), index);
}

void WCDBHandleStatementBindBlob(CPPHandleStatement handleStatement,
                                 int index,
                                 const unsigned char* _Nonnull buffer,
                                 unsigned long long buffLength)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->bindBLOB(
    WCDB::UnsafeData::immutable(buffer, (size_t) buffLength), index);
}

void WCDBHandleStatementBindNull(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturn(handleStatement, WCDB::InnerHandleStatement, cppHandleStatement);
    cppHandleStatement->bindNull(index);
}

WCDBColumnValueType
WCDBHandleStatementGetColumnType(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, WCDBColumnValueTypeNull);
    switch (cppHandleStatement->getType(index)) {
    case WCDB::Syntax::ColumnType::Integer:
        return WCDBColumnValueTypeInterger;
    case WCDB::Syntax::ColumnType::Float:
        return WCDBColumnValueTypeFloat;
    case WCDB::Syntax::ColumnType::BLOB:
        return WCDBColumnValueTypeBLOB;
    case WCDB::Syntax::ColumnType::Text:
        return WCDBColumnValueTypeString;
    case WCDB::Syntax::ColumnType::Null:
        return WCDBColumnValueTypeNull;
    }
}

signed long long WCDBHandleStatementGetInteger(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, 0);
    return cppHandleStatement->getInteger(index);
}

double WCDBHandleStatementGetDouble(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, 0);
    return cppHandleStatement->getDouble(index);
}

const char* _Nullable WCDBHandleStatementGetText(CPPHandleStatement handleStatement, int index)
{
    {
        WCDBGetObjectOrReturnValue(
        handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, nullptr);
        return cppHandleStatement->getText(index).data();
    }
}

const unsigned char*
WCDBHandleStatementGetBlob(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, nullptr);
    return cppHandleStatement->getBLOB(index).buffer();
}

signed long long
WCDBHandleStatementGetColumnSize(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, 0);
    return cppHandleStatement->getColumnSize(index);
}

int WCDBHandleStatementGetColumnCount(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, 0);
    return cppHandleStatement->getNumberOfColumns();
}

const char* _Nullable WCDBHandleStatementGetColumnName(CPPHandleStatement handleStatement, int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, nullptr);
    return cppHandleStatement->getColumnName(index).data();
}

const char* _Nullable WCDBHandleStatementGetOriginalColumnName(CPPHandleStatement handleStatement,
                                                               int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, nullptr);
    return cppHandleStatement->getOriginColumnName(index).data();
}

const char* _Nullable WCDBHandleStatementGetColumnTableName(CPPHandleStatement handleStatement,
                                                            int index)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, nullptr);
    return cppHandleStatement->getColumnTableName(index).data();
}

bool WCDBHandleStatementIsReadOnly(CPPHandleStatement handleStatement)
{
    WCDBGetObjectOrReturnValue(
    handleStatement, WCDB::InnerHandleStatement, cppHandleStatement, false);
    return cppHandleStatement->isReadOnly();
}