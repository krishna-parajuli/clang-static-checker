// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\ndetecta all the function declarations in a given source file");

// matcher for 4th parameter in any function declarations
DeclarationMatcher FuncMatcher =
  functionDecl(hasParameter(3,parmVarDecl().bind("parameterDeclaration"))).bind("functionDeclaration");


class FuncPrinter : public MatchFinder::MatchCallback {
public :
  virtual void run(const MatchFinder::MatchResult &Result) {
    ASTContext *Context = Result.Context;
    const FunctionDecl *funcName = Result.Nodes.getNodeAs<FunctionDecl>("functionDeclaration");
    const VarDecl *ParmVar = Result.Nodes.getNodeAs<VarDecl>("parameterDeclaration");
    // filter AST nodes from header and include files
    if (!ParmVar || !Context->getSourceManager().isWrittenInMainFile(ParmVar->getLocStart()))
      return;
    // generate warning now
    DiagnosticsEngine &DE = Context->getDiagnostics();
    const auto ID = DE.getCustomDiagID(DiagnosticsEngine::Warning,
                                   "function declaration %0 has more than three parameters");

    DiagnosticBuilder DB = DE.Report(ParmVar->getLocStart(), ID);
    DB.AddString(funcName->getName());//get function name in warning
  }
};


int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  FuncPrinter Printer;
  MatchFinder Finder;
  Finder.addMatcher(FuncMatcher, &Printer);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}
