#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
  struct HelloNewPMPass : public PassInfoMixin<HelloNewPMPass> {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
      if(F.hasName())
        errs() << "Hello " << F.getName() << "\n";
      return PreservedAnalyses::all();
    }
  };
} // end anonymous namespace

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "HelloNewPMPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "hello-new-pm-pass"){    //当命令行的参数中有"hello-new-pm-pass"时，就会添加HelloNewPass
            FPM.addPass(HelloNewPMPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}