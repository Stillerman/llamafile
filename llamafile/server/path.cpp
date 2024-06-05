// -*- mode:c++;indent-tabs-mode:nil;c-basic-offset:4;coding:utf-8 -*-
// vi: set et ft=cpp ts=4 sts=4 sw=4 fenc=utf-8 :vi
//
// Copyright 2024 Mozilla Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "path.h"

using namespace ctl;

string
basename(const string_view path) noexcept
{
    size_t i, e;
    if ((e = path.size())) {
        while (e > 1 && path[e - 1] == '/')
            --e;
        i = e - 1;
        while (i && path[i - 1] != '/')
            --i;
        return path.substr(i, e - i);
    } else {
        return ".";
    }
}

string
dirname(const string_view path) noexcept
{
    size_t e = path.size();
    if (e--) {
        for (; path[e] == '/'; e--)
            if (!e)
                return "/";
        for (; path[e] != '/'; e--)
            if (!e)
                return ".";
        for (; path[e] == '/'; e--)
            if (!e)
                return "/";
        return path.substr(0, e + 1);
    }
    return ".";
}

string
resolve(const string_view lhs, const string_view rhs) noexcept
{
    if (lhs.empty())
        return rhs;
    if (!rhs.empty() && rhs[0] == '/')
        return rhs;
    if (!lhs.empty() && lhs[lhs.size() - 1] == '/')
        return string(lhs) + rhs;
    return string(lhs) + "/" + rhs;
}
