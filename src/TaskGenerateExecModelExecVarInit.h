/**
 * TaskGenerateExecModelExecVarInit.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "zsp/be/sw/IOutput.h"
#include "IGenRefExpr.h"

namespace zsp {
namespace be {
namespace sw {

class TaskGenerateExecModel;

class TaskGenerateExecModelExecVarInit :
    public virtual arl::dm::VisitorBase {
public:
    TaskGenerateExecModelExecVarInit(
        TaskGenerateExecModel       *gen,
        IOutput                     *out
    );

    virtual ~TaskGenerateExecModelExecVarInit();

    virtual void generate(arl::dm::ITypeProcStmtVarDecl *var);

    virtual void visitDataTypeAddrClaim(arl::dm::IDataTypeAddrClaim *t) override;

    virtual void visitDataTypeAddrHandle(arl::dm::IDataTypeAddrHandle *t) override;

    virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) override;

private:
    TaskGenerateExecModel               *m_gen;
    IOutput                             *m_out;
    arl::dm::ITypeProcStmtVarDecl       *m_var;

};

}
}
}

