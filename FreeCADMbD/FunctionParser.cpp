#include "FunctionParser.h"
#include "ASMTAssembly.h"
#include "ASMTrIJ.h"
#include "ASMTAngleIJz.h"
#include "ASMTdAngleIJx.h"
#include "ASMTdAngleIJy.h"
#include "ASMTvIJ.h"
#include "ASMTvrIJ.h"
#include "ASMTOmegaIJ.h"
#include "ASMTOmegaIJKi.h"

using namespace MbD;

std::shared_ptr<FunctionParser> FunctionParser::With()
{
    auto inst = std::make_shared<FunctionParser>();
    inst->initialize();
    return inst;
}

void FunctionParser::initgeoIJs()
{
    geoIJs = std::make_shared<std::map<std::string, std::shared_ptr<ASMTSymbolicFunctionIJ>>>();
    auto connectorList = owner->root()->connectorList();
    std::shared_ptr<ASMTSymbolicFunctionIJ> funcIJ;
    for (auto& geoIJ : *connectorList) {
        funcIJ = ASMTSymbolicFunctionIJ::With();
        funcIJ->geoIJ = geoIJ;
        geoIJs->insert(std::make_pair(geoIJ->name, funcIJ));
        if (geoIJ.get() == owner) {
            funcIJ = ASMTSymbolicFunctionIJ::With();
            funcIJ->geoIJ = geoIJ;
            geoIJs->insert(std::make_pair("self", funcIJ));
        }
    }
}

bool FunctionParser::geoIJ()
{
    if ((tokenType == "word") && (geoIJs->count(token) == 1)) {
        auto& var = geoIJs->at(token);
        stack->push(var);
        scanToken();
        return true;
    }
    return false;
}

bool FunctionParser::displacement()
{
    std::shared_ptr<CADSymbolicFunction> symfunc = nullptr;
    if (peekForTypevalue("word", "rIJ")) {
        symfunc = ASMTrIJ::With();
    }
    else if (peekForTypevalue("word", "angleIJz")) {
        symfunc = ASMTAngleIJz::With();
    }
    else if (peekForTypevalue("word", "dAngleIJx")) {
        symfunc = ASMTdAngleIJx::With();
    }
    else if (peekForTypevalue("word", "dAngleIJy")) {
        symfunc = ASMTdAngleIJy::With();
    }
    if (symfunc != nullptr) {
        symfunc->owner = owner;
        stack->push(symfunc);
        if (peekForTypeNoPush("(")) {
            auto startsize = stack->size();
            if (geoIJ()) {
                if (peekForTypeNoPush(")")) {
                    auto itemIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
                    stack->pop();
                    auto funcIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
                    funcIJ->geoIJ = itemIJ->geoIJ;
                    return true;
                }
                expected(")");
            }
            expected("displacement");
        }
        expected("(");
    }
    return false;
}

bool FunctionParser::velocity()
{
    std::shared_ptr<CADSymbolicFunction> symfunc = nullptr;
    if (peekForTypevalue("word", "vIJ")) {
        symfunc = ASMTvIJ::With();
    }
    else if (peekForTypevalue("word", "vrIJ")) {
        symfunc = ASMTvrIJ::With();
    }
    else if (peekForTypevalue("word", "omeIJ")) {
        symfunc = ASMTOmegaIJ::With();
    }
    else if (peekForTypevalue("word", "omeIJKi")) {
        symfunc = ASMTOmegaIJKi::With();
    }
    if (symfunc != nullptr) {
        symfunc->owner = owner;
        stack->push(symfunc);
        if (peekForTypeNoPush("(")) {
            auto startsize = stack->size();
            if (geoIJ()) {
                if (peekForTypeNoPush(")")) {
                    auto itemIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
                    stack->pop();
                    auto funcIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
                    funcIJ->geoIJ = itemIJ->geoIJ;
                    return true;
                }
                else if (peekForTypeNoPush(",")) {
                    auto itemIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
                    stack->pop();
                    auto funcIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJKi>(stack->top());
                    funcIJ->geoIJ = itemIJ->geoIJ;
                    funcIJ->markerKSign = token;
                    assert(token == "I");    //ToDo: J and O
                    scanToken();
                    assert(peekForTypeNoPush(","));
                    assert(tokenType == "number");
                    funcIJ->axisK = (size_t)tokenNum;
                    scanToken();
                    assert(peekForTypeNoPush(")"));
                    return true;
                }
                else {
                    expected(") or ,");
                }
                expected(")");
            }
            expected("velocity");
        }
        expected("(");
    }
    return false;
}

bool FunctionParser::force()
{
    return false;
}

bool FunctionParser::namedFunction()
{
    return intrinsic() || displacement() || velocity() || force();
}
