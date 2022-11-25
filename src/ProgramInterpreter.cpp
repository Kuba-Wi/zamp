#include "ProgramInterpreter.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace xercesc;

bool ProgramInterpreter::ExecProgram(const char* filename) {
    this->CreateInterpCommands();
    this->AddObjectsToScene();

    std::string command;
    this->BuildConfigurationCommand(command);

    if (!communication_.OpenConnection()) {
        return false;
    }
    communication_.Send(command.c_str());

    std::istringstream cmdStream;
    if (!this->ExecPreprocesor(filename, cmdStream)) {
        return false;
    }

    std::string plugin_name;
    while (cmdStream >> plugin_name) {
        if (plugin_name == "Begin_Parallel_Actions") {
            continue;
        }

        if (plugin_name == "End_Parallel_Actions") {
            for (auto& th : threads_list_) {
                th.join();
            }
            threads_list_.clear();
            continue;
        }

        if (LibManager_.find(plugin_name) == LibManager_.end()) {
            std::cout << "No plugin named: " << plugin_name << std::endl;
            return true;
        }

        auto cmd_ptr = LibManager_[plugin_name]->createCmd();
        if (!cmd_ptr) {
            std::cout << "Error in creating command of plugin " << plugin_name << std::endl;
            return true;
        }

        if(!cmd_ptr->ReadParams(cmdStream)) {
            std::cout << "Error in reading parameters of plugin " << plugin_name << std::endl;
            return false;
        }

        threads_list_.emplace_back(std::thread{[&, cmd = std::move(cmd_ptr)](){
            cmd->ExecCmd(Scn_, communication_);
        }});
    }

    for (auto& th : threads_list_) {
        th.join();
    }

    communication_.Close();

    return true;
}

void ProgramInterpreter::BuildConfigurationCommand(std::string& command) {
    std::ostringstream vec_str;
    command = "Clear\n";
    for (const auto& [obj_name, oper_vect] : config_.getObjOperations()) {
        command += "AddObj Name=";
        command += obj_name;
        for (const auto& [op_name, val] : oper_vect) {
            command += " ";
            command += op_name;
            command += "=";
            vec_str = std::ostringstream{};
            vec_str << val;
            command += vec_str.str();
        }
        command += "\n";
    }
}

bool ProgramInterpreter::ExecPreprocesor(const char* filename, std::istringstream &outStream) const {
    constexpr size_t LINE_SIZE = 500;
    char Line[LINE_SIZE];
    std::string Cmd4Preproc = "cpp -P ";
    std::ostringstream OTmpStrm;
    Cmd4Preproc += filename;
    FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

    if (!pProc) {
        return false;
    }

    while (fgets(Line, LINE_SIZE, pProc)) {
        OTmpStrm << Line;
    }
    outStream.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

void ProgramInterpreter::AddObjectsToScene() {
    for (const auto& [obj_name, op_map] : config_.getObjOperations()) {
        Scn_.AddMobileObj(obj_name);
        for (const auto& [op_name, val] : op_map) {
            Scn_.AddObjOperation(obj_name, op_name, val);
        }
    }
}

void ProgramInterpreter::CreateInterpCommands() {
    const std::string prefix{"libInterp4"};
    const std::string postfix{".so"};

    for (auto libname : config_.getLibNames()) {
        if (libname.length() > prefix.length() + postfix.length()) {
            libname.erase(0, prefix.length());
            libname.erase(libname.length() - postfix.length(), libname.length());

            if (!this->CreateInterpCommand(libname)) {
                this->RemoveInterpCommand(libname);
            }
        }
    }
}

bool ProgramInterpreter::CreateInterpCommand(const std::string& libname) {
    LibManager_[libname] = std::make_unique<LibInterface>(LibInterface{libname});
    return LibManager_[libname]->createCmdBuilder();
}

void ProgramInterpreter::RemoveInterpCommand(const std::string& libname) {
    auto it = LibManager_.find(libname);
    if (it != LibManager_.end()) {
        LibManager_.erase(it);
    }
}

bool ProgramInterpreter::Read_XML_Config(const char* sFileName, const char* grammar_file)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(config_);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar(grammar_file,
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}
