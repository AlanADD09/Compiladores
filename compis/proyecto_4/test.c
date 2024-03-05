#include <stdio.h>
#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/ExecutionEngine.h>

int main() {
    LLVMModuleRef module = LLVMModuleCreateWithName("SimpleModule");
    LLVMBuilderRef builder = LLVMCreateBuilder();

    // Crear una función principal
    LLVMTypeRef mainFuncType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef mainFunc = LLVMAddFunction(module, "main", mainFuncType);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(mainFunc, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    // Simular una operación de suma 1+2
    LLVMValueRef sum = LLVMBuildAdd(builder, LLVMConstInt(LLVMInt32Type(), 1, 0),
                                           LLVMConstInt(LLVMInt32Type(), 2, 0), "sum");

    // Retornar el resultado
    LLVMBuildRet(builder, sum);

    // Configurar LLVM
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmPrinters();
    LLVMInitializeAllAsmParsers();

    // Configurar el motor de ejecución
    LLVMExecutionEngineRef engine;
    char *error = NULL;
    LLVMCreateExecutionEngineForModule(&engine, module, &error);

    // Obtener la función 'main' y ejecutarla
    int (*funcPtr)() = (int (*)())LLVMGetFunctionAddress(engine, "main");
    int result = funcPtr();

    // Mostrar el resultado
    printf("Resultado: %d\n", result);

    // Limpiar la memoria
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
    LLVMDisposeModule(module);

    return 0;
}
