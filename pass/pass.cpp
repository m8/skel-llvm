#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Analysis/CostModel.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/Support/InstructionCost.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"

#include "envparser.hpp"

using namespace llvm;

namespace
{
  struct SkelPass : public FunctionPass
  {
    static char ID;

    SkelPass() : FunctionPass(ID)
    {}

    bool runOnFunction(Function &F) override
    {
      return true;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
      AU.addRequired<TargetTransformInfoWrapperPass>();
      AU.addRequired<LoopInfoWrapperPass>();
      AU.addRequired<ScalarEvolutionWrapperPass>();

      AU.addPreserved<TargetTransformInfoWrapperPass>();
      AU.addPreserved<LoopInfoWrapperPass>();
      AU.addPreserved<ScalarEvolutionWrapperPass>();
      AU.setPreservesAll();
    }

    bool doFinalization(Module &M) override
    {
      return false;
    } 
  };
}

char SkelPass::ID = 0;
static RegisterPass<SkelPass> X("SkelPass", "Pass");

static SkelPass *_PassMaker = NULL;

static RegisterStandardPasses _RegPass1(PassManagerBuilder::EP_OptimizerLast,
                                        [](const PassManagerBuilder &, legacy::PassManagerBase &PM)
                                        {
        if(!_PassMaker){ PM.add(_PassMaker = new SkelPass());} }); // ** for -Ox

static RegisterStandardPasses _RegPass2(PassManagerBuilder::EP_EnabledOnOptLevel0,
                                        [](const PassManagerBuilder &, legacy::PassManagerBase &PM)
                                        {
        if(!_PassMaker){ PM.add(_PassMaker = new SkelPass()); } }); // ** for -O0