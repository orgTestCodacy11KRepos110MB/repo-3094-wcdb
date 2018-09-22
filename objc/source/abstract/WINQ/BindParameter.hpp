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

#ifndef BindParameter_hpp
#define BindParameter_hpp

#include <WCDB/Describable.hpp>

namespace WCDB {

class BindParameter : public DescribableWithLang<Lang::BindParameter>, public Redirectable {
public:
    static std::list<Expression> bindParameters(int count);
    //    enum class Type : int {
    //        Colon = (int) Lang::BindParameter::Type::Colon,           //:AAAA
    //        At = (int) Lang::BindParameter::Type::At,                 //@AAAA
    //        DollarSign = (int) Lang::BindParameter::Type::DollarSign, //$AAAA
    //    };

    explicit BindParameter(int n); // ?NNN
    //    explicit BindParameter(const std::string &name,
    //                           const Type &type = Type::Colon);

protected:
    Expression getRedirectSource() const override;
};

} // namespace WCDB

#endif /* BindParameter_hpp */