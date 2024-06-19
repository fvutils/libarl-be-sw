/*
 * GenRefExprExecModel.cpp
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
#include "GenRefExprExecModel.h"
#include "TaskGenerateExecModel.h"


namespace zsp {
namespace be {
namespace sw {


GenRefExprExecModel::GenRefExprExecModel(
        TaskGenerateExecModel       *gen,
        vsc::dm::IDataTypeStruct    *ctxt,
        const std::string           &ctxtRef,
        bool                        ctxtPtr) :
        m_gen(gen), m_ctxt(ctxt), m_ctxtRef(ctxtRef), m_ctxtPtr(ctxtPtr) {
    DEBUG_INIT("zsp::be::sw::GenRefExprExecModel", gen->getDebugMgr());

}

GenRefExprExecModel::~GenRefExprExecModel() {

}

std::string GenRefExprExecModel::genLval(vsc::dm::ITypeExpr *ref) {
    m_ret.clear();
    m_depth = 0;
    ref->accept(m_this);
    return m_ret;
}

std::string GenRefExprExecModel::genRval(vsc::dm::ITypeExpr *ref) {
    m_ret.clear();
    m_depth = 0;
    ref->accept(m_this);
    return m_ret;
}

void GenRefExprExecModel::visitTypeExprRefBottomUp(vsc::dm::ITypeExprRefBottomUp *e) {
    DEBUG_ENTER("visitTypeExprRefBottomUp");
    arl::dm::ITypeProcStmtScope *scope = m_scope_s.at(
        m_scope_s.size()-e->getScopeOffset()-1
    );
    arl::dm::ITypeProcStmtVarDecl *var = scope->getVariables().at(e->getSubFieldIndex()).get();
    m_ret.append(var->name());

    DEBUG_LEAVE("visitTypeExprRefBottomUp");
}

void GenRefExprExecModel::visitTypeExprRefPath(vsc::dm::ITypeExprRefPath *e) { 
    DEBUG_ENTER("visitTypeExprRefPath");

    DEBUG_LEAVE("visitTypeExprRefPath");
}

void GenRefExprExecModel::visitTypeExprRefTopDown(vsc::dm::ITypeExprRefTopDown *e) { 
    DEBUG_ENTER("visitTypeExprRefTopDown");
    m_ret.append(m_ctxtRef);
    m_type = m_ctxt;

    if (m_depth) {
        m_ret.append(m_ctxtPtr?"->":".");
    }
    DEBUG_LEAVE("visitTypeExprRefTopDown");
}

void GenRefExprExecModel::visitTypeExprSubField(vsc::dm::ITypeExprSubField *e) { 
    DEBUG_ENTER("visitTypeExprSubField");
    m_depth++;
    e->getRootExpr()->accept(m_this);
    m_depth--;

    vsc::dm::ITypeField *field = dynamic_cast<vsc::dm::IDataTypeStruct *>(m_type)->getField(e->getSubFieldIndex());
    m_ret.append(field->name());
    m_type = field->getDataType();

    if (m_depth) {
        // TODO: should determine based on field type
        m_ret.append(".");
    }


    DEBUG_LEAVE("visitTypeExprSubField");
}

dmgr::IDebug *GenRefExprExecModel::m_dbg = 0;

}
}
}