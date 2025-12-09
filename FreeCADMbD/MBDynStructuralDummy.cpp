#include "MBDynStructuralDummy.h"
#include "MBDynReference.h"
#include "ASMTMarker.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynStructuralDummy> MBDynStructuralDummy::With()
{
    auto inst = std::make_shared<MBDynStructuralDummy>();
    inst->initialize();
    return inst;
}

void MBDynStructuralDummy::parseMBDyn(std::string line)
{
    strucString = line;
    arguments = collectArgumentsFor("structural", line);
    readLabel(arguments);
    auto nodeType = readStringNoSpacesOffTop(arguments);
    assert(nodeType == "dummy");
    baseNodeName = readStringNoSpacesOffTop(arguments);
    auto offsetStr = readStringNoSpacesOffTop(arguments);
    assert(offsetStr == "offset");
    readPosition(arguments);
    readOrientation(arguments);
}

void MBDynStructuralDummy::readPosition(std::vector<std::string>& args)
{
    rOfO = std::make_shared<FullColumn<double>>(3);
    if (args.empty()) return;
    if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        baseRefName = readStringNoSpacesOffTop(args);
        auto& ref = mbdynReferences()->at(baseRefName);
        auto rFfF = readBasicPosition(args);
        auto& rOFO = ref->rFfF;
        auto& aAOF = ref->aAFf;
        rOfO = rOFO->plusFullColumn(aAOF->timesFullColumn(rFfF));
    }
    else if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
    }
    else {
        rOfO = readBasicPosition(args);
    }
}

void MBDynStructuralDummy::readOrientation(std::vector<std::string>& args)
{
    aAOf = FullMatrix<double>::identitysptr(3);
    if (args.empty()) return;
    if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        assert(baseRefName == readStringNoSpacesOffTop(args));
        auto& ref = mbdynReferences()->at(baseRefName);
        auto aAFf = readBasicOrientation(args);
        auto& aAOF = ref->aAFf;
        aAOf = aAOF->timesFullMatrix(aAFf);
    }
    else if (args[0].find("position") != std::string::npos) {
        if (args[0].find("orientation") != std::string::npos) {
            args.erase(args.begin());
            aAOf = readBasicOrientation(args);
        }
    }
    else if (args[0].find("orientation") != std::string::npos) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            assert(baseRefName == readStringNoSpacesOffTop(args));
            aAOf = readBasicOrientation(args);
        }
    }
    else {
        aAOf = readBasicOrientation(args);
    }
}

void MBDynStructuralDummy::createASMT()
{
    auto asmtMarker = ASMTMarker::With();
    asmtItem = asmtMarker;
    asmtMarker->setName(label);
    asmtMarker->setPosition3D(rOfO);
    asmtMarker->setRotationMatrix(aAOf);
    auto asmtParts = asmtAssembly()->parts;
    auto it = std::find_if(asmtParts->begin(), asmtParts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
        return prt->name == baseNodeName;
        });
    auto& asmtPart = *it;
    asmtPart->addMarker(asmtMarker);
}

void MBDynStructuralDummy::outputLine(size_t i, std::ostream& os)
{
    auto id = labelIDat(label);
    auto r = rOmO(i);
    auto x = r->at(0);
    auto y = r->at(1);
    auto z = r->at(2);
    auto aA = aAOm(i);
    auto v = vOmO(i);
    auto vx = v->at(0);
    auto vy = v->at(1);
    auto vz = v->at(2);
    auto ome = omeOmO(i);
    auto omex = ome->at(0);
    auto omey = ome->at(1);
    auto omez = ome->at(2);
    os << id << " ";
    os << x << " " << y << " " << z << " ";
    auto row = aA->at(0);
    os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
    row = aA->at(1);
    os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
    row = aA->at(2);
    os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
    os << vx << " " << vy << " " << vz << " ";
    os << omex << " " << omey << " " << omez << " ";
    os << std::endl;
}

FColDsptr MBDynStructuralDummy::rOmO(size_t i)
{
    auto asmtMarker = std::static_pointer_cast<ASMTMarker>(asmtItem);
    return asmtMarker->rOfO(i);
}

FMatDsptr MBDynStructuralDummy::aAOm(size_t i)
{
    auto asmtMarker = std::static_pointer_cast<ASMTMarker>(asmtItem);
    return asmtMarker->aAOf(i);
}

FColDsptr MBDynStructuralDummy::vOmO(size_t i)
{
    auto asmtMarker = std::static_pointer_cast<ASMTMarker>(asmtItem);
    return asmtMarker->vOfO(i);
}

FColDsptr MBDynStructuralDummy::omeOmO(size_t i)
{
    auto asmtMarker = std::static_pointer_cast<ASMTMarker>(asmtItem);
    return asmtMarker->omeOfO(i);
}
