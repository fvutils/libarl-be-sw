/*
 * TaskGenerateExecModelExecScopeNB.cpp
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
#include "dmgr/impl/DebugMacros.h"
#include "TaskGenerateExecModel.h"
#include "TaskGenerateExecModelExecScopeNB.h"


namespace zsp {
namespace be {
namespace sw {


TaskGenerateExecModelExecScopeNB::TaskGenerateExecModelExecScopeNB(
    TaskGenerateExecModel   *gen,
    IOutput                 *out) : m_dbg(0), m_gen(gen), m_out(out) {
    DEBUG_INIT("zsp::be::sw::TaskGenerateExecModelExecScopeNB", gen->getDebugMgr());
}

TaskGenerateExecModelExecScopeNB::~TaskGenerateExecModelExecScopeNB() {

}

void TaskGenerateExecModelExecScopeNB::generate(
        arl::dm::ITypeExec                      *i,
        bool                                    new_scope) {
    m_out_s.push_back(OutputExecScope(new_scope, m_out));
    i->accept(m_this);
    m_out_s.back().apply(m_out);
}

void TaskGenerateExecModelExecScopeNB::generate(
        const std::vector<arl::dm::ITypeExecUP> &i,
        bool                                    new_scope) {

    for (std::vector<arl::dm::ITypeExecUP>::const_iterator
        it=i.begin();
        it!=i.end(); it++) {
        m_out_s.push_back(OutputExecScope(new_scope, m_gen->getOutC()));
        (*it)->accept(m_this);
        m_out_s.back().apply(m_gen->getOutC());
        new_scope |= (i.size() > 1);
    }
}

void TaskGenerateExecModelExecScopeNB::visitTypeProcStmtAssign(arl::dm::ITypeProcStmtAssign *s) {
    DEBUG_ENTER("visitTypeProcStmtAssign");
    m_out_s.back().exec()->println("// assignment");
    DEBUG_LEAVE("visitTypeProcStmtAssign");
}

void TaskGenerateExecModelExecScopeNB::visitTypeProcStmtVarDecl(arl::dm::ITypeProcStmtVarDecl *s) {
    DEBUG_ENTER("visitTypeProcStmtVarDecl");
    m_out_s.back().decl()->println("// declaration");
    DEBUG_LEAVE("visitTypeProcStmtVarDecl");
}

}
}
}
